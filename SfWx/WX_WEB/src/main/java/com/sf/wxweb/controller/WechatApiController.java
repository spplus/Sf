package com.sf.wxweb.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/wechat")
public class WechatApiController {

    @RequestMapping("toMall")
    public String toMall() {
        return "mall/index";
    }

    @RequestMapping("toServiceOrders")
    public String toServiceOrders() {
        return "serviceorders/index";
    }

    @RequestMapping("toAppointment")
    public String toAppointment() {
        return "appointment/index";
    }

    @RequestMapping("toHealthLife")
    public String toHealthLife() {
        return "healthlife/index";
    }

    @RequestMapping("toMyAppliance")
    public String toMyAppliance() {
        return "myappliance/index";
    }
}
