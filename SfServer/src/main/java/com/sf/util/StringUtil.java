package com.sf.util;

import java.io.IOException;
import java.io.Writer;
import java.math.BigDecimal;
import java.net.InetAddress;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.codehaus.jackson.map.ObjectMapper;
import org.codehaus.jackson.map.SerializationConfig.Feature;
import org.dom4j.Document;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.XMLWriter;

public class StringUtil {

    /**
     * <li>判断列表是否为空值</li> <li>NULL、size为0均认为空值</li>
     * 
     * @param value
     * @return
     */
    public static boolean isEmptyList(List<?> list) {
        return null == list || list.size() == 0;
    }

    /**
     * 判断字符串是0或者是""或者是null
     * 
     * @param value
     * @return
     */
    public static boolean isZeroOrEmpty(String value) {
        return isEmpty(value) || "0".equals(value.trim());
    }

    /**
     * <li>判断列表是否为空值</li> <li>NULL、size为0均认为空值</li>
     * 
     * @param value
     * @return
     */
    public static boolean isNotEmptyList(List<?> list) {
        return !isEmptyList(list);
    }

    /**
     * <li>判断对象是否为空字符串</li> <li>NULL、空格均认为空字符串</li>
     * 
     * @param value
     * @return
     */
    public static boolean isNotEmpty(Object value) {
        return !isEmpty(value);
    }

    /**
     * 判定中文字符串的長度
     * 
     * @param value
     *            字符串
     * @return
     */
    public static int length(String value) {
        int valueLength = 0;
        if (value != null) {
            String chinese = "[\u0391-\uFFE5]";
            /* 获取字段值的长度，如果含中文字符，则每个中文字符长度为2，否则为1 */
            for (int i = 0; i < value.length(); i++) {
                /* 获取一个字符 */
                String temp = value.substring(i, i + 1);
                /* 判断是否为中文字符 */
                if (temp.matches(chinese)) {
                    /* 中文字符长度为2 */
                    valueLength += 2;
                } else {
                    /* 其他字符长度为1 */
                    valueLength += 1;
                }
            }
        }

        return valueLength;
    }

    /**
     * List转为ListMap
     * 
     * @param paramName
     *            要转换的参数名
     * @param paramMap
     *            参数Map
     */
    public static <E> List<Map<String, Object>> listToListMap(String paramName, List<E> list) {
        if (list == null) {
            return null;
        }
        List<Map<String, Object>> mapList = new ArrayList<Map<String, Object>>();
        Map<String, Object> map = null;
        for (E str : list) {
            map = new HashMap<String, Object>();
            map.put(paramName, str);
            mapList.add(map);
        }
        return mapList;
    }

    /**
     * 对象为Null时转换成""返回,其他返回其toString值
     * 
     * @param value
     * @return 转换后字符串
     */
    public static String null2String(Object value) {
        if (null == value) {
            return "";
        } else {
            return value.toString();
        }
    }

    /**
     * 对象为Null时直接返回,其他返回其toString值
     * 
     * @param value
     * @return 转换后字符串
     */
    public static String object2String(Object value) {
        if (null == value) {
            return null;
        } else {
            return value.toString();
        }
    }

    /**
     * <li>判断字符串是否为空值</li> <li>NULL、空格均认为空值</li>
     * 
     * @param value
     * @return
     */
    public static boolean isEmpty(String value) {
        return null == value || "".equals(value.trim());
    }

    /**
     * <li>判断对象是否为空字符串</li> <li>NULL、空格均认为空字符串</li>
     * 
     * @param value
     * @return
     */
    public static boolean isEmpty(Object value) {
        return null == value || "".equals(value.toString().trim());
    }

    /**
     * <li>判断字符串是否为空值</li> <li>NULL、空格均认为空值</li>
     * 
     * @param value
     * @return
     */
    public static boolean isNotEmpty(String value) {
        return !isEmpty(value);
    }

    /**
     * 重复字符串 如 repeatString("a",3) ==> "aaa"
     * 
     * @author sumaojun@nowdecision.com
     * @param src
     * @param repeats
     * @return
     */
    public static String repeatString(String src, int repeats) {
        if (null == src || repeats <= 0) {
            return src;
        } else {
            StringBuffer bf = new StringBuffer();
            for (int i = 0; i < repeats; i++) {
                bf.append(src);
            }
            return bf.toString();
        }
    }

    /**
     * 左对齐字符串 * lpadString("X",3); ==>" X" *
     * 
     * @param src
     * @param length
     * @return
     */
    public static String lpadString(String src, int length) {
        return lpadString(src, length, " ");
    }

    /**
     * 以指定字符串填补空位，左对齐字符串 * lpadString("X",3,"0"); ==>"00X"
     * 
     * @param src
     * @param byteLength
     * @param temp
     * @return
     */
    public static String lpadString(String src, int length, String single) {
        if (src == null || length <= src.getBytes().length) {
            return src;
        } else {
            return repeatString(single, length - src.getBytes().length) + src;
        }
    }

    /**
     * 右对齐字符串 * rpadString("9",3)==>"9 "
     * 
     * @param src
     * @param byteLength
     * @return
     */
    public static String rpadString(String src, int byteLength) {
        return rpadString(src, byteLength, " ");
    }

    /**
     * 以指定字符串填补空位，右对齐字符串 rpadString("9",3,"0")==>"900"
     * 
     * @param src
     * @param byteLength
     * @param single
     * @return
     */
    public static String rpadString(String src, int length, String single) {
        if (src == null || length <= src.getBytes().length) {
            return src;
        } else {
            return src + repeatString(single, length - src.getBytes().length);
        }
    }

    /**
     * 去除,分隔符，用于金额数值去格式化
     * 
     * @param value
     * @return
     */
    public static String decimal(String value) {
        if (null == value || "".equals(value.trim())) {
            return "0";
        } else {
            return value.replaceAll(",", "");
        }
    }

    /**
     * 在数组中查找字符串
     * 
     * @param params
     * @param name
     * @param ignoreCase
     * @return
     */
    public static int indexOf(String[] params, String name, boolean ignoreCase) {
        if (params == null)
            return -1;
        for (int i = 0, j = params.length; i < j; i++) {
            if (ignoreCase && params[i].equalsIgnoreCase(name)) {
                return i;
            } else if (params[i].equals(name)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 将字符转数组
     * 
     * @param str
     * @return
     */
    public static String[] toArr(String str) {
        String inStr = str;
        String a[] = null;
        try {
            if (null != inStr) {
                StringTokenizer st = new StringTokenizer(inStr, ",");
                if (st.countTokens() > 0) {
                    a = new String[st.countTokens()];
                    int i = 0;
                    while (st.hasMoreTokens()) {
                        a[i++] = st.nextToken();
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return a;
    }

    /**
     * 字符串数组包装成字符串
     * 
     * @param ary
     * @param s
     *            包装符号如 ' 或 "
     * @return
     */
    public static String toStr(String[] ary, String s) {
        if (ary == null || ary.length < 1)
            return "";
        StringBuffer bf = new StringBuffer();
        bf.append(s);
        bf.append(ary[0]);
        for (int i = 1; i < ary.length; i++) {
            bf.append(s).append(",").append(s);
            bf.append(ary[i]);
        }
        bf.append(s);
        return bf.toString();
    }

    /**
     * 设置MESSAGE中的变量{0}...{N}
     * 
     * @param msg
     * @param vars
     * @return
     */
    public static String getMessage(String msg, String[] vars) {
        for (int i = 0; i < vars.length; i++) {
            msg = msg.replaceAll("\\{" + i + "\\}", vars[i]);
        }
        return msg;
    }

    /**
     * @param msg
     * @param var
     * @return
     */
    public static String getMessage(String msg, String var) {
        return getMessage(msg, new String[] { var });
    }

    /**
     * @param msg
     * @param var
     * @param var2
     * @return
     */
    public static String getMessage(String msg, String var, String var2) {
        return getMessage(msg, new String[] { var, var2 });
    }

    /**
     * 将key=value;key2=value2……转换成Map
     * 
     * @param params
     * @return
     */
    public static Map<Object, Object> gerneryParams(String params) {
        Map<Object, Object> args = new HashMap<Object, Object>();
        if (!isEmpty(params)) {
            try {
                String map, key, value;
                StringTokenizer st = new StringTokenizer(params, ";");
                StringTokenizer stMap;
                while (st.hasMoreTokens()) {
                    map = st.nextToken();
                    if (isEmpty(map.trim()))
                        break;
                    stMap = new StringTokenizer(map, "=");
                    key = stMap.hasMoreTokens() ? stMap.nextToken() : "";
                    if (isEmpty(key.trim()))
                        continue;
                    value = stMap.hasMoreTokens() ? stMap.nextToken() : "";
                    args.put(key, value);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return args;
    }

    /**
     * 页面格式化日期:yyyyMMdd ---> yyyy-MM-dd
     * 
     * @param date
     * @return
     */
    public static String formatDate(String date) {
        return isEmpty(date) ? "" : DateUtil.format(date, "yyyyMMdd", "yyyy-MM-dd");
    }

    /**
     * 解析文件的扩展名
     * 
     * @param oldName
     * @return
     */
    public static String getFileExtName(String oldName) {
        String ext = "";
        int lastIndex = oldName.lastIndexOf(".");
        if (lastIndex > 0) {
            ext = oldName.substring(lastIndex);
        }
        return ext;
    }

    public static void generyXmlEntry(StringBuffer bf, String entry, Object value) {
        bf.append("<").append(entry).append(">");
        if (null != value)
            bf.append(value);
        bf.append("</").append(entry).append(">");
    }

    public static void generyXmlEntryCData(StringBuffer bf, String entry, Object value) {
        bf.append("<").append(entry).append("><![CDATA[");
        if (null != value)
            bf.append(value);
        bf.append("]]></").append(entry).append(">");
    }

    public static String generyImgUrl(Object rootUrl, Object date, Object imgId, Object imgInfo) {
        StringBuffer bf = new StringBuffer();
        try {
            String ext = StringUtil.getFileExtName((String) imgInfo);
            bf.append(rootUrl).append("/");
            bf.append(date).append("/");
            bf.append(imgId).append(ext);
        } catch (Exception e) {
            bf.append("");
        }
        return bf.toString();
    }

    /**
     * 格式化xml数据
     * 
     * @param stringWriter
     * @param doc
     * @throws IOException
     */
    public static void formateXMLStr(Writer stringWriter, Document doc) throws IOException {
        OutputFormat of = new OutputFormat();
        of.setIndent(true);
        of.setEncoding("UTF-8");
        of.setNewlines(true);
        XMLWriter xmlWriter = new XMLWriter(stringWriter, of);
        xmlWriter.write(doc);
        xmlWriter.close();
    }

    public static final String randomString(int length) {
        if (length < 1) {
            return null;
        }
        Random randGen = null;
        char[] numbersAndLetters = null;
        randGen = new Random();
        numbersAndLetters = ("0123456789abcdefghijklmnopqrstuvwxyz" + "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")
                .toCharArray();
        char[] randBuffer = new char[length];
        for (int i = 0; i < randBuffer.length; i++) {
            randBuffer[i] = numbersAndLetters[randGen.nextInt(71)];
        }
        return new String(randBuffer);
    }

    public static String replacePwdFormXMl(String log) {
        log = log.replaceAll("<Password>.*?</Password>", "<Password></Password>");
        log = log.replaceAll("<FundTransPwd>.*?</FundTransPwd>", "<FundTransPwd></FundTransPwd>");
        return log;
    }

    public static int string2Int(String s) {
        if (s == null || "".equals(s) || "undefined".equals(s))
            return 0;
        int result = 0;
        try {
            if (s.indexOf(",") != -1) {
                s = s.substring(0, s.indexOf(","));
            } else if (s.indexOf(".") != -1) {
                s = s.substring(0, s.indexOf("."));
            } else if (s.indexOf("|") != -1) {
                s = s.substring(0, s.indexOf("|"));
            }
            result = Integer.parseInt(s);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return result;
    }

    /**
     * 以给定分隔符分割字符串并返回分割后List
     * 
     * @param s
     *            分割用字符串
     * @param seprator
     *            分隔符(例:",")
     * @return 分割后List
     */
    public static List<String> string2List(String s, String seprator) {
        ArrayList<String> sList = null;
        if (isNotEmpty(s) && isNotEmpty(seprator)) {
            String[] sArr = s.split(seprator);
            sList = new ArrayList<String>(sArr.length);
            for (String sa : sArr) {
                sList.add(sa);
            }
        }
        return sList;
    }

    public static boolean string2Boolean(String s) {
        if (s == null || "".equals(s) || "undefined".equals(s) || "false".equals(s))
            return false;
        return true;
    }

    public static int parseInt(String str, int defalut) {
        if (isNumericNT(str)) {
            return Integer.parseInt(str);
        } else {
            return defalut;
        }
    }

    public static long parseLong(String str, long defalut) {
        if (isNumericNT(str)) {
            return Long.parseLong(str);
        } else {
            return defalut;
        }
    }

    public static double parseDouble(String str, double defalut) {
        double d = defalut;
        try {
            d = Double.parseDouble(str);
        } catch (Exception e) {
        }
        return d;
    }

    public static boolean isNumericNT(String str) {
        Pattern pattern = Pattern.compile("(-)?[1-9][0-9]*");// [1-9]*");
        Matcher isNum = pattern.matcher(str);
        if (!isNum.matches()) {
            return false;
        }
        return true;
    }

    public static boolean isCharaterAndNumber(String str) {
        String reg = "[0-9a-zA-Z]*";
        Pattern pattern = Pattern.compile(reg);
        return pattern.matcher(str).matches();

    }

    /**
     * 
     * @Title: mountformat
     * @Description: 格式化金额 123456 => 123456.00
     * @param mount
     * @return
     * @return String
     * @throws
     * @author shenqiancheng@nowdecision.com
     */
    public static String mountformat(Double mount) {
        DecimalFormat myformat = new DecimalFormat();
        myformat.applyPattern("###,###,###,###,###.00");
        String fm = myformat.format(mount);
        if (fm.startsWith(".")) {
            fm = "0" + fm;
        }
        return fm;
    }

    public static String getIp() {
        try {
            InetAddress addr = InetAddress.getLocalHost();
            String ip = addr.getHostAddress().toString();// 获得本机IP
            // String address=addr.getHostName().toString();//获得本机名称
            return ip;
        } catch (Exception e) {
            return "";
        }
    }

    /**
     * @param t
     *            数据类型：基本类型(待添加自定义JavaBean)
     * @param text
     *            节点Value
     * @return 转换后的节点Value
     * @author sumaojun@nowdecision.com
     */
    @SuppressWarnings("rawtypes")
    public static Object setBeanValue(Class t, String text) {
        try {
            if (t == Integer.class) {
                return new Integer(Integer.parseInt(text));
            } else if (t == Double.class) {
                return new Double(Double.parseDouble(text));
            } else if (t == Float.class) {
                return new Float(Float.parseFloat(text));
            } else if (t == Long.class) {
                return new Long(Long.parseLong(text));
            } else if (t == Boolean.class) {
                return new Boolean(Boolean.parseBoolean(text));
            } else if (t == Byte.class) {
                return new Byte(Byte.parseByte(text));
            } else if (t == Date.class) {
                return DateUtil.parseDate(text, "yyyy-MM-dd HH:mm:ss");
            } else if (t == BigDecimal.class) {
                return BigDecimal.valueOf(Double.parseDouble(text));
            } else if (t.getSimpleName().equals("int")) {
                return Integer.parseInt(text);
            } else if (t.getSimpleName().equals("float")) {
                return Float.parseFloat(text);
            } else if (t.getSimpleName().equals("double")) {
                return Double.parseDouble(text);
            } else if (t.getSimpleName().equals("long")) {
                return Long.parseLong(text);
            } else if (t.getSimpleName().equals("boolean")) {
                return Boolean.parseBoolean(text);
            } else if (t.getSimpleName().equals("byte")) {
                return Byte.parseByte(text);
            } else {
                return text;
            }
        } catch (Exception e) {
            e.printStackTrace();
            e.getMessage();
        }
        return text;
    }

    /**
     * 正则查找替换， 使用方法： String regex = "\\$\\{(.+?)\\}"; String str =
     * "<a onclick=\"showUserName('${CRECODE}','${session.user.password}');\" >linkme</a>"
     * ; Map<String,Object> map=new HashMap<String, Object>();
     * map.put("CRECODE", "0-1111");
     * System.out.println(regReplace(str,regex,map));;
     * 
     * @param str
     * @param regex
     * @param replaceMap
     * @return
     */
    public static String regReplace(String str, String regex, Map<String, Object> replaceMap) {
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str);
        StringBuffer sb = new StringBuffer();
        while (matcher.find()) {
            String key = str.substring(matcher.start() + 2, matcher.end() - 1);
            String value = "";
            if (!replaceMap.containsKey(key)) {
                matcher.appendReplacement(sb, value);
            } else {
                if (replaceMap.containsKey(key)) {
                    Object _value = replaceMap.get(key);
                    if (_value != null) {
                        value = String.valueOf(_value);
                        matcher.appendReplacement(sb, value);
                    }
                }
            }

        }
        matcher.appendTail(sb);
        return sb.toString();
    }

    public static Map<String, Object> mapKey2LowCase(Map<String, Object> map) {
        Map<String, Object> newMap = new HashMap<String, Object>();
        for (String key : map.keySet()) {
            newMap.put(key.toLowerCase(), map.get(key));
        }
        return newMap;
    }
    
    /**
     * 将Map key，统一转成大写
     * 
     * @param map
     * @return
     */
    public static Map<String, Object> mapKey2UpperCase(Map<String, Object> map) {
        Map<String, Object> newMap = new HashMap<String, Object>();
        for (String key : map.keySet()) {
            newMap.put(key.toUpperCase(), map.get(key));
        }
        return newMap;
    }    

    /**
     * 空数组判断
     * 
     * @param array
     * @return boolean 結果
     */
    public static boolean isEmptyArray(final Object[] array) {
        return array == null || array.length <= 0;
    }

    /**
     * 空数组判断
     * 
     * @param lst
     * @return boolean 結果
     */
    public static String getMsgWithParam(final String msg, Object[] params) {
        String newmsg = msg;
        if (!isEmpty(msg) && !isEmptyArray(params)) {
            for (Object param : params) {
                if (param != null) {
                    newmsg = newmsg.replaceFirst("@param@", param.toString());
                }
            }
        }
        return newmsg;
    }

    @SuppressWarnings({ "deprecation", "unchecked" })
    public static Map<String, Object> jsonStringToMap(String text) {
        ObjectMapper objectMapper = new ObjectMapper().configure(Feature.WRITE_NULL_PROPERTIES, false);
        try {
            return objectMapper.readValue(text, Map.class);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static <T> T jsonStringToBean(String text, Class<T> t) {
        ObjectMapper objectMapper = new ObjectMapper().configure(Feature.WRITE_NULL_PROPERTIES, false);
        objectMapper.enableDefaultTyping();
        try {
            return objectMapper.readValue(text, t);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    @SuppressWarnings("deprecation")
    public static String toJsonString(Object b) {
        ObjectMapper objectMapper = new ObjectMapper().configure(Feature.WRITE_NULL_PROPERTIES, false);
        try {
            String jsonStr = objectMapper.writeValueAsString(b);
            return jsonStr;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private static String getFixLenthString(int strLength) {

        Random rm = new Random();

        // 获得随机数
        double pross = (1 + rm.nextDouble()) * Math.pow(10, strLength);

        // 将获得的获得随机数转化为字符串
        String fixLenthString = String.valueOf(pross);

        // 返回固定的长度的随机数
        return fixLenthString.substring(1, strLength + 1);
    }

    @SuppressWarnings("deprecation")
    public static String GetOrderNo(String sequence, String custno) {
        int length = sequence.length();
        String random = "";
        if ((12 - length) > 5)
            random = getFixLenthString(12 - length - 5) + getFixLenthString(5);
        else {
            random = getFixLenthString(12 - length);
        }

        String CustlastNumber = custno.substring(custno.length() - 4, custno.length());

        String OrderNo = sequence + random + CustlastNumber;
        return OrderNo;
    }

    /**
     * @title 比较版本号
     * @param msg
     * @param map
     */
    public static boolean IsNeedUpgrade(String cver, String sver) {
        String[] cver_array = cver.split("\\.");
        String[] sver_array = sver.split("\\.");
        int cver_size = cver_array.length;
        int sver_size = sver_array.length;
        if (cver_size < 3 || sver_size < 3) {
            return false;
        }

        // 比较第一位
        if (Integer.parseInt(sver_array[0]) > Integer.parseInt(cver_array[0])) {
            return true;
        }
        // 第一位相等，比较第二位
        else if (Integer.parseInt(sver_array[0]) == Integer.parseInt(cver_array[0])) {
            if (Integer.parseInt(sver_array[1]) > Integer.parseInt(cver_array[1])) {
                return true;
            }
            // 第二位相等，比较第三位
            else if (Integer.parseInt(sver_array[1]) == Integer.parseInt(cver_array[1])) {
                if (Integer.parseInt(sver_array[2]) > Integer.parseInt(cver_array[2])) {
                    return true;
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    /**
     * 判断是否是手机号码
     * @param mobiles
     * @return
     */
    public static boolean isMobileNum(String mobiles) {
        if (StringUtil.isEmpty(mobiles)) {
            return true;
        }
        Pattern p = Pattern.compile("^((13[0-9])|(14[57])|(15[0-9])|(17[0678])|(18[0-9]))\\d{8}$");
        Matcher m = p.matcher(mobiles);
        return m.matches();
    }
    
    /**
     * 去除传入字符的首尾空格
     * 
     * @param obj
     * @return
     */
    public static String trim(Object obj) {
        if (StringUtil.isNotEmpty(obj)) {
            return String.valueOf(obj).trim();
        } else {
            return null;
        }
    }

    /**
     * 判断是否是邮箱地址
     * 
     * @param email
     * @return
     */
    public static boolean isEmail(String email) {
        if (StringUtil.isEmpty(email)) {
            return true;
        }
        Pattern p = Pattern.compile("[\\w]+@[\\w]+.[\\w]+");
        Matcher m = p.matcher(email);
        return m.matches();
    }

    /**
     *  判断是否是正整数.
     * @param str
     * @return
     */
    public static boolean isNumeric(String str){
        Pattern pattern = Pattern.compile("[0-9]*");
        return pattern.matcher(str).matches();
    }
}
