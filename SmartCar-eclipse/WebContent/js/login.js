function onLogin() {
    var phone = $('#input-phone').val();
    var password = $('#input-password').val();
    //console.log(phone+password);
    var rememberPassword = $('#checkbox-remember-password').prop('checked');
    var autoLogin = $('#checkbox-auto-login').prop('checked');
    $.post(
        "user_login.jsp",
        {
            user_phone: phone,
            user_password: password
        },
        function (data, status) {
        	var data_back=data.split('\n')[0].replace(/[\r\n]/g,"");
        	console.log(data_back);
            if (status === 'success'&&data_back=='true') {
                if (rememberPassword) {
                    localStorage.setItem('savedLoginInfo', JSON.stringify({phone: phone, password: password}));
                }
                if (autoLogin) {
                    localStorage.setItem('autoLogin', true);
                }
                location.href = "home.html";
            } else {
                alert("登录失败，请检查网络连接");
            }
        }
    );
}