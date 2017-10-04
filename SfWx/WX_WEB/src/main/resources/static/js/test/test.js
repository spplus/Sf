// 页面配置
$(document).ready(function() {
	//alert('ok');
});

// 查询按钮押下
function onAddUser() {

	addUser();
}

// 新增用户
function addUser(){
	var url = "adduser";
	doPost(url);
}


function doPost(postUrl) {
	var searchCondition = new Object() ;
	searchCondition.id="1";

	$.ajax({
		url : postUrl,
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
