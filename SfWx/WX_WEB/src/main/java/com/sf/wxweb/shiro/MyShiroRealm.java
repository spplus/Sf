package com.sf.wxweb.shiro;

import org.apache.shiro.authc.AuthenticationException;
import org.apache.shiro.authc.AuthenticationInfo;
import org.apache.shiro.authc.AuthenticationToken;
import org.apache.shiro.authc.SimpleAuthenticationInfo;
import org.apache.shiro.authc.UsernamePasswordToken;
import org.apache.shiro.authz.AuthorizationInfo;
import org.apache.shiro.authz.SimpleAuthorizationInfo;
import org.apache.shiro.realm.AuthorizingRealm;
import org.apache.shiro.subject.PrincipalCollection;
import org.apache.shiro.util.ByteSource;
import org.springframework.beans.factory.annotation.Autowired;

import com.sf.sfcm.bean.UserInfo;
import com.sf.wxweb.provider.WxServiceProvider;


public class MyShiroRealm extends AuthorizingRealm {
	@Autowired
	WxServiceProvider dbServiceClient;
	
    @Override
    protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principals) {
        System.out.println("权限配置-->MyShiroRealm.doGetAuthorizationInfo()");
        SimpleAuthorizationInfo authorizationInfo = new SimpleAuthorizationInfo();
        UserInfo userInfo  = (UserInfo)principals.getPrimaryPrincipal();
        /*
        for(SysRole role:userInfo.getRoleList()){
            authorizationInfo.addRole(role.getRole());
            for(SysPermission p:role.getPermissions()){
                authorizationInfo.addStringPermission(p.getPermission());
            }
        }
        */
        return authorizationInfo;
    }

    /*主要是用来进行身份认证的，也就是说验证用户输入的账号和密码是否正确。*/
    @Override
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token)
            throws AuthenticationException {
    	
//        SpLogger.debug("MyShiroRealm.doGetAuthenticationInfo()");
        
        UsernamePasswordToken authcToken = (UsernamePasswordToken) token;
        
        //获取用户的输入的账号.
        String username = (String)token.getPrincipal();
//        SpLogger.debug(token.getCredentials());
        
        //通过username从数据库中查找 User对象，如果找到，没找到.
        //实际项目中，这里可以根据实际情况做缓存，如果不做，Shiro自己也是有时间间隔机制，2分钟内不会重复执行该方法
     
//        UserInfo userInfo = SpringUtil.getEntrance().getDbservice().findUserByUserName(username);
        
        UserInfo userInfo = dbServiceClient.findUserByUserName(username);
        
//        SpLogger.debug("----->>userInfo="+userInfo.getName());
        if(userInfo == null){

            return null;
        }
        
        authcToken.getPassword();

        return new SimpleAuthenticationInfo(
                userInfo, //用户名
                userInfo.getPassword(), //密码
                ByteSource.Util.bytes(userInfo.getCredentialsSalt()),//salt=username+salt
                getName()  //realm name
        );
    }

}