function setPageHtml(totalCount, currentPage, totalPage) {
	var pageHtml = "";
	pageHtml += "<span>共" + totalCount + "条</span>";
	pageHtml += "<span>" + currentPage + "/" + totalPage + "页 </span>";
	if (currentPage == 1 || currentPage == 0) {
		pageHtml += "<span>首页</span>";
	} else {
		pageHtml += "<span><a href='javascript:' onclick='searchFirstData();' style='color:#2369FF;'>首页</a></span>";
	}
	if (currentPage == 1 || currentPage == 0) {
		pageHtml += "<span>上一页</span>";
	} else {
		pageHtml += "<span><a href='javascript:' onclick='searchPreData();' style='color:#2369FF;'>上一页</a></span>";
	}
	if (currentPage == totalPage) {
		pageHtml += "<span>下一页<span>";
	} else {
		pageHtml += "<span><a href='javascript:' onclick='searchNextData();' style='color:#2369FF;'>下一页</a></span>";
	}
	if (currentPage == totalPage) {
		pageHtml += "<span>末页</span>";
	} else {
		pageHtml += "<span><a href='javascript:' onclick='searchLastData();' style='color:#2369FF;'>末页</a></span>";
	}
	pageHtml += "跳转到<input id='appPage' type='text' class='page_text' value='' onkeyup='cutNumber(this);' onblur='cutNumber(this);' />页";
	pageHtml += "<input type='button' class='page_btn' onclick='goAppPage(this);' value='go' />";
	return pageHtml;
}
// 切除非数字
function cutNumber(obj) {
	obj.value = obj.value.replace(/[^0-9]/g, '');
}
// 输入页码后按enter键处理
function setPageEnterFunction() {
	$('#appPage').keypress(function(event) {
		if (event["keyCode"] == 13) {
			var appPage = $('#appPage').val();
			if (appPage > $('#totalPage').val()) {
				artDialog.alert('输入的页数不能大于总页数，请重新输入');
			} else if (appPage == 0) {
				artDialog.alert('请输入正确的页数');
			} else {
				searchPageData();
			}
		}
	});
}
function goAppPage(obj) {
	var appPage = $('#appPage').val();
	if (appPage > $('#totalPage').val()) {
		artDialog.alert('输入的页数不能大于总页数，请重新输入');
	} else if (appPage == 0) {
		artDialog.alert('请输入正确的页数');
	} else {
		searchPageData();
	}
}