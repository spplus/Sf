package com.sf.sfcm.util;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

/**
 * 日期格式化
 * 
 */
public class DateUtil {

	public static final String DATE_FORMATTER = "yyyy-MM-dd";

	public static final String DATE_FORMATTER_HMS = "yyyy-MM-dd HH:mm:ss";

	public static final String DATE_FORMATTER_HMS_SSS = "yyyy-MM-dd HH:mm:ss.SSS";

	public static final String DATE_FORMATTER_WEEK = "yyyy-MM-dd E";
	public static String formatDataToChinaData(Calendar c){
		if(c==null){
			c = Calendar.getInstance();  
		}
		return formatDateToStr( c.getTime(),"yyyy年MM月dd日 HH:mm:ss");
	}
	public static java.util.Date parseDate(String dateStr, String format) {
		java.util.Date date = null;
		DateFormat df = new SimpleDateFormat(format);
		try {
			date = df.parse(dateStr);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		
		return date;
	}

	public static java.util.Date parseDate(String dateStr) {
		return parseDate(dateStr, DATE_FORMATTER);
	}

	public static String todayStr() {
		return formatDateToStr(new Date(), DATE_FORMATTER);
	}

	public static Date today() {
		return parseDate(todayStr(), DATE_FORMATTER);
	}
	public static Date todayAndTime() {
		String today = formatDateToStr(new Date(), DATE_FORMATTER_HMS);
		return parseDate(today, DATE_FORMATTER_HMS);
	}

	/**
	 * @param date
	 *            需要格式化的日期对像
	 * @param formatter
	 *            格式化的字符串形式
	 * @return 按照formatter指定的格式的日期字符串
	 * @throws ParseException
	 *             无法解析的字符串格式时抛出
	 */
	public static String formatDateToStr(Date date, String formatter) {
		if (date == null)
			return "";
		try {
			return new java.text.SimpleDateFormat(formatter,Locale.CHINA).format(date);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return "";
	}

	/**
	 * 生成默认格式的日期
	 * 
	 * @param date
	 * @return
	 */
	public static String formatDateToStr(Date date) {
		return formatDateToStr(date, DATE_FORMATTER);
	}

	/**
	 * 将日期按照指定的模式格式化
	 * 
	 * @param date
	 *            {@link Date}
	 * @param format
	 *            如：yyyy/MM/dd
	 * @return 返回空表示格式化产生异常
	 */
	public static String format(java.util.Date date, String format) {
		String result = "";
		try {
			if (date != null) {
				java.text.DateFormat df = new java.text.SimpleDateFormat(format);
				result = df.format(date);
			}
		} catch (Exception e) {
		}
		return result;
	}

	/**
	 * 字符串型日期格式转换
	 * 
	 * @param sDate
	 *            formatFrom格式的日期字符串
	 * @param formatFrom
	 *            转换前格式
	 * @param formatTo
	 *            转换后格式
	 * 
	 * @return formatTo格式的日期字符串
	 */
	public static String getDateWeek(String sDate, String formatFrom,
			String formatTo) {
		try {
			SimpleDateFormat format = new SimpleDateFormat(formatFrom);
			Date date = format.parse(sDate);
			format.applyPattern(formatTo);
			return format.format(date);
		} catch (Exception ex) {
			return sDate;
		}
	}

	/**
	 * 将一种字符日期转化成另外一种日期格式
	 * 
	 * @param date
	 * @param fmtSrc
	 * @param fmtTag
	 * @return
	 */
	public static String format(String date, String fmtSrc, String fmtTag) {
		if (null == fmtSrc)
			return null;
		if (fmtSrc.equals(fmtTag)) {
			return date;
		}
		String year, month, daty;
		int Y, M, D;
		fmtSrc = fmtSrc.toUpperCase();
		Y = fmtSrc.indexOf("YYYY");
		M = fmtSrc.indexOf("MM");
		D = fmtSrc.indexOf("DD");
		if (Y < 0 || M < 0 || D < 0) {
			return date;
		}
		year = date.substring(Y, Y + 4);
		month = date.substring(M, M + 2);
		daty = date.substring(D, D + 2);
		fmtTag = fmtTag.toUpperCase();
		fmtTag = fmtTag.replaceAll("YYYY", year);
		fmtTag = fmtTag.replaceAll("MM", month);
		fmtTag = fmtTag.replaceAll("DD", daty);
		return fmtTag;
	}

	/**
	 * 计算指定年月的日期数
	 * 
	 * @param year
	 * @param month
	 * @return
	 */
	public static int maxDayOfMonth(int year, int month) {
		switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			boolean isRunYear = (year % 400 == 0)
					|| (year % 4 == 0 && year % 100 != 0);
			return isRunYear ? 29 : 28;
		default:
			return 31;
		}
	}

	/**
	 * 获取指定年月的日期数
	 * 
	 * @param year
	 * @param month
	 * @return
	 */
	public static int maxDayOfMonth(String year, String month) {
		return maxDayOfMonth(Integer.parseInt(year), Integer.parseInt(month));
	}

	/**
	 * 获取指定年月上月月末日期
	 * 
	 * @param year
	 * @param month
	 * @return
	 */
	public static String getLastMonthDate(String year, String month) {
		return getLastMonthDate(Integer.parseInt(year), Integer.parseInt(month));
	}

	/**
	 * 获取指定年月上月月末日期
	 * 
	 * @param year
	 * @param month
	 * @return
	 */
	public static String getLastMonthDate(int year, int month) {
		if (month <= 1) {
			year -= 1;
			month = 12;
		} else {
			month -= 1;
		}
		StringBuffer bfDate = new StringBuffer();
		bfDate.append(year);
		if (month < 10)
			bfDate.append("0");
		bfDate.append(month);
		bfDate.append(maxDayOfMonth(year, month));
		return bfDate.toString();
	}

	/**
	 * 提前N天的日期
	 * 
	 * @param date
	 * @param days
	 * @return
	 */
	public static Date beforeDate(Date date, int days) {
		java.util.Calendar c = java.util.Calendar.getInstance();
		c.setTime(date);
		c.add(java.util.Calendar.DAY_OF_YEAR, -days);
		return c.getTime();

	}

	/**
	 * 一周前的日期
	 * 
	 * @return
	 */
	public static Date getLastWeek() {
		java.util.Calendar c = java.util.Calendar.getInstance();
		c.add(java.util.Calendar.DAY_OF_YEAR, -7);
		return c.getTime();

	}

	public static int curHour(Calendar cal) {
		return cal.get(Calendar.HOUR_OF_DAY);
	}

	public static int curMinute(Calendar cal) {
		return cal.get(Calendar.MINUTE);
	}

	public static int curSecond(Calendar cal) {
		return cal.get(Calendar.SECOND);
	}

	public static String curTimeStr() {
		Calendar cal = Calendar.getInstance();
		// 分别取得当前日期的年、月、日
		StringBuffer bf = new StringBuffer(10);
		int hour = cal.get(Calendar.HOUR_OF_DAY);
		if (hour < 10)
			bf.append("0");
		bf.append(hour);
		bf.append(":");
		int minite = cal.get(Calendar.MINUTE);
		if (minite < 10)
			bf.append("0");
		bf.append(minite);
		bf.append(":");
		int second = cal.get(Calendar.SECOND);
		if (second < 10)
			bf.append("0");
		bf.append(second);
		return bf.toString();
	}

	/***************************************************************************
	 * @功能 计算当前日期某年的第几周
	 * @return interger
	 * @throws ParseException
	 **************************************************************************/
	public static int getWeekNumOfYear() {
		Calendar calendar = Calendar.getInstance();
		int iWeekNum = calendar.get(Calendar.WEEK_OF_YEAR);
		return iWeekNum;
	}

	/***************************************************************************
	 * @功能 计算指定日期某年的第几周
	 * @return interger
	 * @throws ParseException
	 **************************************************************************/
	public static int getWeekNumOfYearDay(String strDate) {
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(parseDate(strDate));
		int iWeekNum = calendar.get(Calendar.WEEK_OF_YEAR);
		return iWeekNum;
	}

	/***************************************************************************
	 * @功能 计算某年某周的开始日期
	 * @return interger
	 * @throws ParseException
	 **************************************************************************/
	public static String getWeekFirstDay(int yearNum, int weekNum) {
		Calendar cal = Calendar.getInstance();
		cal.set(Calendar.YEAR, yearNum);
		cal.set(Calendar.WEEK_OF_YEAR, weekNum);
		cal.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
		// 分别取得当前日期的年、月、日
		String tempYear = Integer.toString(yearNum);
		String tempMonth = Integer.toString(cal.get(Calendar.MONTH) + 1);
		String tempDay = Integer.toString(cal.get(Calendar.DATE));
		return tempYear + "-" + tempMonth + "-" + tempDay;
	}

	public static String getWeekFirstDay(int weekNum) {
		Calendar cal = Calendar.getInstance();
		cal.set(Calendar.WEEK_OF_YEAR, weekNum);
		cal.set(Calendar.DAY_OF_WEEK, Calendar.MONDAY);
		// 分别取得当前日期的年、月、日
		String tempMonth = Integer.toString(cal.get(Calendar.MONTH) + 1);
		String tempDay = Integer.toString(cal.get(Calendar.DATE));
		return cal.get(Calendar.YEAR) + "-" + tempMonth + "-" + tempDay;
	}

	/***************************************************************************
	 * @功能 计算某年某周的结束日期
	 * @return interger
	 * @throws ParseException
	 **************************************************************************/
	public static String getWeekEndDay(int yearNum, int weekNum) {
		Calendar cal = Calendar.getInstance();
		cal.set(Calendar.YEAR, yearNum);
		cal.set(Calendar.WEEK_OF_YEAR, weekNum + 1);
		cal.set(Calendar.DAY_OF_WEEK, Calendar.SUNDAY);
		// 分别取得当前日期的年、月、日
		String tempMonth = Integer.toString(cal.get(Calendar.MONTH) + 1);
		String tempDay = Integer.toString(cal.get(Calendar.DATE));
		return cal.get(Calendar.YEAR) + "-" + tempMonth + "-" + tempDay;
	}

	public static String getWeekEndDay(int weekNum) {
		Calendar cal = Calendar.getInstance();
		cal.set(Calendar.WEEK_OF_YEAR, weekNum + 1);
		cal.set(Calendar.DAY_OF_WEEK, Calendar.SUNDAY);
		// 分别取得当前日期的年、月、日
		String tempMonth = Integer.toString(cal.get(Calendar.MONTH) + 1);
		String tempDay = Integer.toString(cal.get(Calendar.DATE));
		return cal.get(Calendar.YEAR) + "-" + tempMonth + "-" + tempDay;
	}

	/**
	 * date:传进来的时间 len:需要改变的天数，正负均可
	 */

	public static String getDay(String date, int len) {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		try {
			Calendar cal = Calendar.getInstance();
			cal.setTime(sdf.parse(date));
			cal.add(Calendar.DATE, len);
			return sdf.format(cal.getTime());
		} catch (Exception e) {
			return date;
		}
	}

	/**
	 * len:距离今天的天数，正负均可
	 */

	public static String getDay(int len) {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
		String date = sdf.format(new Date());
		try {
			Calendar cal = Calendar.getInstance();
			cal.setTime(sdf.parse(date));
			cal.add(Calendar.DATE, len);
			return sdf.format(cal.getTime());
		} catch (Exception e) {
			return date;
		}
	}

	/**
	 * 获取当前时间
	 */
	public static String getToDate() {
		SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMATTER_HMS_SSS);
		String date = sdf.format(new Date());
		return date;
	}

	/**
	 * String 转 Date yyyy-MM-dd HH:mm:ss.SSS
	 */
	public static Date getStrToDateByAll(String time) {
		Date date = new Date();
		SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMATTER_HMS_SSS);
		try {
			date = sdf.parse(time);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return date;
	}

	/**
	 * String 转 Date yyyy-MM-dd
	 */
	public static Date getStrToDateByTen(String time) {
		Date date = new Date();
		SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMATTER);
		try {
			date = sdf.parse(time);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return date;
	}

	/**
	 * @param dateStr
	 * @param inFormat
	 * @param toFormat
	 * @return toFormat time
	 * @message 将传入时间格式转换成传出时间格式
	 */
	public static String formatStrDateToStr(String dateStr, String inFormat,
			String toFormat) {
		SimpleDateFormat sf = new SimpleDateFormat(inFormat);
		Date date;
		String time = "";
		try {
			date = sf.parse(dateStr);
			sf = new SimpleDateFormat(toFormat);
			time = sf.format(date);
		} catch (ParseException e) {
			e.printStackTrace();
		}

		return time;
	}

	// 获得日期是一周的第几天，星期日是第一天，星期二是第二天......
	private static int getMondayPlus(Calendar cd) {

		int dayOfWeek = cd.get(Calendar.DAY_OF_WEEK);
		if (dayOfWeek == 1) {
			return 7;
		} else {
			return dayOfWeek - 1;
		}
	}

	/**
	 * @Title: getPreDay
	 * @Description: 获取相对某天的过去日期
	 * @param cal
	 *            某天的日期
	 * @param num
	 *            相对某天的数目
	 * @param state
	 *            0代表相对天，1代表相对月
	 * @return String 日期字符串
	 * @throws
	 */
	private static String getPreDay(Calendar cal, int num, int state) {
		if (state == 0) {
			cal.add(Calendar.DAY_OF_MONTH, -num);
		} else if (state == 1) {
			cal.add(Calendar.MONTH, -num);
		}
		return format(cal.getTime(), DATE_FORMATTER);
	}

	/**
	 * @Title: getDatesByState
	 * @Description:根据state状态（周，月，季度，半年，年）获取相应的起始时间和结束时间
	 * @param state
	 *            统计时间段状态
	 * @return Map<String,String> 本期起始日期，本期结束日期， 上期起始日期，上期结束日期文本
	 * @throws
	 */
	public static Map<String, String> getDatesByState(String state) {
		Map<String, String> map = new HashMap<String, String>();
		Calendar cal = Calendar.getInstance(Locale.CHINA);
		map.put("curEndDate", format(cal.getTime(), DATE_FORMATTER));
		// 周信息
		if ("1".equals(state)) {
			int dayPeriod = getMondayPlus(cal);
			map.put("curStartDate", getPreDay(cal, dayPeriod - 1, 0));
			map.put("preEndDate", getPreDay(cal, 1, 0));
			map.put("preStartDate", getPreDay(cal, 6, 0));
			// 月信息
		} else if ("2".equals(state)) {
			cal.set(Calendar.DAY_OF_MONTH, 1);
			map.put("curStartDate", format(cal.getTime(), DATE_FORMATTER));
			map.put("preEndDate", getPreDay(cal, 1, 0));
			cal.set(Calendar.DAY_OF_MONTH, 1);
			map.put("preStartDate", format(cal.getTime(), DATE_FORMATTER));
			// 季度信息
		} else if ("3".equals(state)) {
			cal.set(Calendar.DAY_OF_MONTH, 1);
			map.put("curStartDate", getPreDay(cal, 2, 1));
			map.put("preEndDate", getPreDay(cal, 1, 0));
			cal.set(Calendar.DAY_OF_MONTH, 1);
			map.put("preStartDate", getPreDay(cal, 2, 1));
			// 半年信息
		} else if ("4".equals(state)) {
			cal.set(Calendar.DAY_OF_MONTH, 1);
			map.put("curStartDate", getPreDay(cal, 5, 1));
			map.put("preEndDate", getPreDay(cal, 1, 0));
			cal.set(Calendar.DAY_OF_MONTH, 1);
			map.put("preStartDate", getPreDay(cal, 5, 1));
			// 年信息
		} else if ("5".equals(state)) {
			cal.set(Calendar.DAY_OF_MONTH, 1);
			cal.set(Calendar.MONTH, 0);
			map.put("curStartDate", format(cal.getTime(), DATE_FORMATTER));
			map.put("preEndDate", getPreDay(cal, 1, 0));
			cal.set(Calendar.DAY_OF_MONTH, 1);
			cal.set(Calendar.MONTH, 0);
			map.put("preStartDate", format(cal.getTime(), DATE_FORMATTER));
		}
		return map;

	}
	public static Date formatStrToDateByLength(String dateStr) {
		if (StringUtil.isEmpty(dateStr)) {
			return null;
		}
		int strLength = dateStr.length();
		Date date = new Date();
		String dateFormat = DATE_FORMATTER;
		SimpleDateFormat sdf = null;
		try {
			if (strLength >= 14 && strLength < 20) {// yyyyMMddHHmmss 或更大
				dateFormat = DATE_FORMATTER_HMS;
			} else {
				dateFormat = DATE_FORMATTER_HMS_SSS;
			}
			sdf = new SimpleDateFormat(dateFormat);
			date = sdf.parse(dateStr);
		} catch (ParseException e) {
			e.printStackTrace();
			return null;
		}
		return date;
	}

}
