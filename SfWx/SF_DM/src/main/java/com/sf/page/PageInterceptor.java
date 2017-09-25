package com.sf.page;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.Properties;

import org.apache.ibatis.executor.ErrorContext;
import org.apache.ibatis.executor.ExecutorException;
import org.apache.ibatis.executor.statement.BaseStatementHandler;
import org.apache.ibatis.executor.statement.RoutingStatementHandler;
import org.apache.ibatis.executor.statement.StatementHandler;
import org.apache.ibatis.mapping.BoundSql;
import org.apache.ibatis.mapping.MappedStatement;
import org.apache.ibatis.mapping.ParameterMapping;
import org.apache.ibatis.mapping.ParameterMode;
import org.apache.ibatis.plugin.Interceptor;
import org.apache.ibatis.plugin.Intercepts;
import org.apache.ibatis.plugin.Invocation;
import org.apache.ibatis.plugin.Plugin;
import org.apache.ibatis.plugin.Signature;
import org.apache.ibatis.reflection.MetaObject;
import org.apache.ibatis.reflection.SystemMetaObject;
import org.apache.ibatis.reflection.property.PropertyTokenizer;
import org.apache.ibatis.scripting.xmltags.ForEachSqlNode;
import org.apache.ibatis.session.Configuration;
import org.apache.ibatis.type.TypeHandler;
import org.apache.ibatis.type.TypeHandlerRegistry;

/**
 * 判断如果参数中有 {@link PageUtil} 对象，那么执行分页查询。(1.查询总数并放入page对象中。
 * 2.构造带有limit子句的sql替换原始的sql)
 * 目前只支持把page放到HashMap中(或使用接口时，把page作为方法的参数),并且key为"page"
 */
@Intercepts({ @Signature(type = StatementHandler.class, method = "prepare", args = { Connection.class}) })
@SuppressWarnings("rawtypes")
public class PageInterceptor implements Interceptor {
	public static final String PAGE_KEY = "page";
	private String dialect = "oracle";
	private String pageSqlId = ".*listPage.*"; // mapper.xml中需要拦截的ID(正则匹配)
	
	@Override 
	public Object intercept(Invocation ivk) throws Throwable {
		if (ivk.getTarget() instanceof RoutingStatementHandler) {
			RoutingStatementHandler statementHandler = (RoutingStatementHandler) ivk.getTarget();
			MetaObject metaStatementHandler  = SystemMetaObject.forObject(statementHandler);  
			BaseStatementHandler handler = (BaseStatementHandler)metaStatementHandler.getValue("delegate");
			MappedStatement ms = (MappedStatement) metaStatementHandler.getValue("delegate.mappedStatement");
//			BaseStatementHandler handler = (BaseStatementHandler) ReflectHelper.getValueByFieldName(statementHandler,
//					"delegate");
//			MappedStatement ms = (MappedStatement) ReflectHelper.getValueByFieldName(handler, "mappedStatement");
			if (ms.getId().matches(pageSqlId)) { // 拦截需要分页的SQL
				BoundSql bs = handler.getBoundSql();
				Object param = bs.getParameterObject();
				String sql = bs.getSql();
				if (param instanceof HashMap) {
					HashMap map = (HashMap) param;
					PageUtil p = (PageUtil) map.get(PAGE_KEY);
					if (p != null) {
						p.setTotal(queryTotal(ivk, ms, bs, param, sql));
						BoundSql newbs = new BoundSql(ms.getConfiguration(), pageSql(sql, p), bs.getParameterMappings(), param);
						metaStatementHandler.setValue("delegate.boundSql", newbs);
//						ReflectHelper.setValueByFieldName(bs, "sql", pageSql(sql, p));
					}
				}
			}
		}
		return ivk.proceed();
	}

	/**
	 * 为count语句设置参数.
	 * 
	 * @see org.apache.ibatis.executor.parameter.DefaultParameterHandler#setParameters(PreparedStatement)
	 * @param ps
	 * @param ms
	 * @param bs
	 * @param parameterObject
	 * @throws SQLException
	 */
	private void setParameters(PreparedStatement ps, MappedStatement ms, BoundSql bs, Object parameterObject)
			throws SQLException {
		
//		new DefaultParameterHandler(ms,parameterObject,bs).setParameters(ps);
		
		
		ErrorContext.instance().activity("setting parameters").object(ms.getParameterMap().getId());
		List<ParameterMapping> mappings = bs.getParameterMappings();
		if (mappings == null) {
			return;
		}
		Configuration configuration = ms.getConfiguration();
		TypeHandlerRegistry typeHandlerRegistry = configuration.getTypeHandlerRegistry();
		MetaObject metaObject = parameterObject == null ? null : configuration.newMetaObject(parameterObject);
		for (int i = 0; i < mappings.size(); i++) {
			ParameterMapping parameterMapping = mappings.get(i);
			if (parameterMapping.getMode() != ParameterMode.OUT) {
				
				Object value;
				String propertyName = parameterMapping.getProperty();
				PropertyTokenizer prop = new PropertyTokenizer(propertyName);
				if (parameterObject == null) {
					value = null;
				} else if (typeHandlerRegistry.hasTypeHandler(parameterObject.getClass())) {
					value = parameterObject;
				} else if (bs.hasAdditionalParameter(propertyName)) {
					value = bs.getAdditionalParameter(propertyName);
				} else if (propertyName.startsWith(ForEachSqlNode.ITEM_PREFIX)
						&& bs.hasAdditionalParameter(prop.getName())) {
					value = bs.getAdditionalParameter(prop.getName());
					if (value != null) {
						value = configuration.newMetaObject(value).getValue(
								propertyName.substring(prop.getName().length()));
					}
				} else {
					value = metaObject == null ? null : metaObject.getValue(propertyName);
				}
				TypeHandler typeHandler = parameterMapping.getTypeHandler();
				if (typeHandler == null) {
					throw new ExecutorException("There was no TypeHandler found for parameter " + propertyName
							+ " of statement " + ms.getId());
				}
				typeHandler.setParameter(ps, i + 1, value, parameterMapping.getJdbcType());
				
				
				
				
			}
		}
	}

	/**
	 * 生成特定数据库的分页语句
	 * 
	 * @param sql
	 * @param page
	 * @return
	 */
	private String pageSql(String sql, PageUtil page) {
		if (page == null || dialect == null || dialect.equals("")) {
			return sql;
		}
		StringBuilder sb = new StringBuilder();
		if ("oracle".equals(dialect)) {
			sb.append("select * from (select tmp_tb.*,to_number(ROWNUM) row_id from (");
			sb.append(sql);
			sb.append(")  tmp_tb where to_number(ROWNUM)<=");
			sb.append(page.getCurrentResult() + page.getSize());
			sb.append(") where to_number(row_id)>");
			sb.append(page.getCurrentResult());
		} else if("mysql".equals(dialect)){
			sb.append(sql);
			sb.append(" limit ");
			sb.append(page.getCurrentResult());
			sb.append(",");
			sb.append(page.getSize());
		}else {
			throw new IllegalArgumentException("分页插件不支持此数据库：" + dialect);
		}
		return sb.toString();
	}

	public Object plugin(Object arg0) {
		return Plugin.wrap(arg0, this);
	}

	public void setProperties(Properties p) {
		dialect = p.getProperty("dialect");
	}

	/**
	 * 查询总数
	 * 
	 * @param ivk
	 * @param ms
	 * @param boundSql
	 * @param param
	 * @param sql
	 * @throws SQLException
	 */
	private int queryTotal(Invocation ivk, MappedStatement ms, BoundSql boundSql, Object param, String sql)
			throws SQLException {
		Connection conn = (Connection) ivk.getArgs()[0];
		String countSql = "select count(0) from (" + sql + ") tmp_count";

		BoundSql bs = new BoundSql(ms.getConfiguration(), sql, boundSql.getParameterMappings(), param);
		MetaObject metabs  = SystemMetaObject.forObject(boundSql); 
		MetaObject metaParamsField = (MetaObject)metabs.getValue("metaParameters");
		if (metaParamsField != null) {
			try {
//				mo = (MetaObject) ReflectHelper.getValueByFieldName(boundSql, "metaParameters");
				SystemMetaObject.forObject(bs).setValue("metaParameters", metaParamsField);
//				ReflectHelper.setValueByFieldName(bs, "metaParameters", metaParamsField);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		ResultSet rs = null;
		PreparedStatement stmt = null;
		int count = 0;
		try {
			stmt = conn.prepareStatement(countSql);
			setParameters(stmt, ms, bs, param);
			rs = stmt.executeQuery();
			if (rs.next()) {
				count = rs.getInt(1);
			}
		} finally {
			if (rs != null) {
				rs.close();
				stmt.close();
			}
		}
		return count;
	}

	public String getDialect() {
		return dialect;
	}

	public void setDialect(String dialect) {
		this.dialect = dialect;
	}

	public String getPageSqlId() {
		return pageSqlId;
	}

	public void setPageSqlId(String pageSqlId) {
		this.pageSqlId = pageSqlId;
	}
}
