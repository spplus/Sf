package com.sf.wxweb.config;

import org.springframework.boot.context.properties.ConfigurationProperties;

/**
 * wechat mp properties
 *
 * @author gaols
 */
@ConfigurationProperties(prefix = "wechat.mp.menu")
public class WechatMpMenuProperties {
    /**
     * 商城链接
     */
    private String mallUrl;
    /**
     * 服务工单链接
     */
    private String serviceOrdersUrl;
    /**
     * 预约服务链接
     */
    private String appointmentUrl;
    /**
     * 我的家电
     */
    private String myApplianceUrl;
    /**
     * 健康生活链接
     */
    private String healthLifeUrl;
    private String base;

    public String getMallUrl() {
        return mallUrl;
    }

    public void setMallUrl(String mallUrl) {
        this.mallUrl = mallUrl;
    }

    public String getServiceOrdersUrl() {
        return serviceOrdersUrl;
    }

    public void setServiceOrdersUrl(String serviceOrdersUrl) {
        this.serviceOrdersUrl = serviceOrdersUrl;
    }

    public String getAppointmentUrl() {
        return appointmentUrl;
    }

    public void setAppointmentUrl(String appointmentUrl) {
        this.appointmentUrl = appointmentUrl;
    }

    public String getMyApplianceUrl() {
        return myApplianceUrl;
    }

    public void setMyApplianceUrl(String myApplianceUrl) {
        this.myApplianceUrl = myApplianceUrl;
    }

    public String getHealthLifeUrl() {
        return healthLifeUrl;
    }

    public void setHealthLifeUrl(String healthLifeUrl) {
        this.healthLifeUrl = healthLifeUrl;
    }

    public String getBase() {
        return base;
    }

    public void setBase(String base) {
        this.base = base;
    }
}
