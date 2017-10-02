// 页面配置
$(document).ready(function() {
	alert('ok');
});

// 查询按钮押下
function onAddUser() {
	alert('add user');
}

function search() {
	var searchCondition = getSearchCondition();
	// 清除无数据提示
	$("#noDataDiv").remove();
	var searchURL =  "getList";
	$.ajax({
		url : searchURL,
		data : JSON.stringify(searchCondition),
		type : "POST",
		contentType : "application/json; charset=UTF-8",
		dataType : "json",
		success : function(result) {
			if (result.success) {
				// 服务器处理成功
				showData(result);
				
			} else {
				// 服务器处理错误
				//handleAjaxResponseError(result);
			}
		}
	});
}
function showData(result) {
	
	$("#res").text(result);
	
}
