package com.sf.wxweb.utils;

import me.chanjar.weixin.mp.util.json.WxMpGsonBuilder;

/**
 * @author Binary
 */
public class JsonUtils {
    public static String toJson(Object obj) {
        return WxMpGsonBuilder.create().toJson(obj);
    }
}
