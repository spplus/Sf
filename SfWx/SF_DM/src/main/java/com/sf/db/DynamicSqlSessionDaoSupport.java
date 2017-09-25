/**
 * 
 */
package com.sf.db;

import java.util.Map;

import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.mybatis.spring.SqlSessionTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.dao.support.DaoSupport;
import org.springframework.util.Assert;

/**
 * 可切换数据源的Dao支持类
 * 
 * 
 */
public class DynamicSqlSessionDaoSupport extends DaoSupport {
	/** 可用Sql Session Factory */
	private Map<Object, SqlSessionFactory> targetSqlSessionFactorys;
	/** 默认SQL Session Factory */
	private SqlSessionFactory defaultTargetSqlSessionFactory;
	private SqlSession sqlSession;
	private boolean externalSqlSession;

	
	@Autowired(required = false)
	public final void setSqlSessionFactory(@Qualifier("sqlSessionFactoryDb1")SqlSessionFactory sqlSessionFactory) {
		if (!this.externalSqlSession) {
			this.sqlSession = new SqlSessionTemplate(sqlSessionFactory);
		}
	}

	@Autowired(required = false)
	public final void setSqlSessionTemplate(SqlSessionTemplate sqlSessionTemplate) {
		this.sqlSession = sqlSessionTemplate;
		this.externalSqlSession = true;
	}

	/**
	 * Users should use this method to get a SqlSession to call its statement
	 * methods This is SqlSession is managed by spring. Users should not
	 * commit/rollback/close it because it will be automatically done.
	 * 
	 * @return Spring managed thread safe SqlSession
	 */
	public final SqlSession getSqlSession() {
		// Dao取得SqlSession时，重新设置session
		// factory，以便在切换数据库后确保在事务管理中创建新的Session，解决事务中无法切换数据源的问题
		SqlSessionFactory targetSqlSessionFactory = targetSqlSessionFactorys.get(DataSourceSwitch.getDataSourceType());
		if (targetSqlSessionFactory != null) {
			setSqlSessionFactory(targetSqlSessionFactory);
		} else if (defaultTargetSqlSessionFactory != null) {
			setSqlSessionFactory(defaultTargetSqlSessionFactory);
		}
		return this.sqlSession;
	}

	/**
	 * {@inheritDoc}
	 */
	protected void checkDaoConfig() {
		Assert.notNull(this.sqlSession, "Property 'sqlSessionFactory' or 'sqlSessionTemplate' are required");
	}

	/**
	 * @return the targetSqlSessionFactorys
	 */
	public Map<Object, SqlSessionFactory> getTargetSqlSessionFactorys() {
		return targetSqlSessionFactorys;
	}

	/**
	 * @param targetSqlSessionFactorys
	 *            the targetSqlSessionFactorys to set
	 */
	public void setTargetSqlSessionFactorys(Map<Object, SqlSessionFactory> targetSqlSessionFactorys) {
		this.targetSqlSessionFactorys = targetSqlSessionFactorys;
	}

	/**
	 * @return the defaultTargetSqlSessionFactory
	 */
	public SqlSessionFactory getDefaultTargetSqlSessionFactory() {
		return defaultTargetSqlSessionFactory;
	}

	/**
	 * @param defaultTargetSqlSessionFactory
	 *            the defaultTargetSqlSessionFactory to set
	 */
	public void setDefaultTargetSqlSessionFactory(SqlSessionFactory defaultTargetSqlSessionFactory) {
		this.defaultTargetSqlSessionFactory = defaultTargetSqlSessionFactory;
	}
}
