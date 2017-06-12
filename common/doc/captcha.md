## 获取验证码接口

GET http://localhost:8000/captcha

接口返回

```
{
    "captcha": "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",
    "sid": "32DB7A9C0091B3D0F4F325AC3064F208",
    "success": true,
    "t": 1497253683277
}
```

接口返回数据说明:

* captcha   是图片验证码字节流的 base64 编码，使用时需要使用 base64 解码得到原始的字节流。
* success   如果为 true 表明获取验证码成功，否则表示验证获取失败
* sid       是验证码绑定的 session id
* t         为验证码的产生时间 （Unix timestamp）

## 美的登录接口

POST http://localhost:8000/login
Content-Type: application/json

请求体示例：

```
{
    "user": "AE3413006639", 
    "pwd": "LBwb6888315", 
    "factory": "midea", 
    "xcode": "cg01", 
    "t": 1497253683277, 
    "sid": "F06A61C4ADB3682B7F0F51A1D7666CCF", 
    "mainServerHost": "http://192.168.2.23:8780/netDC/main/receiveOrders", 
    "statusReportHost": "http://local.b"
}
```

**注意这里新增了三个参数 xcode、t 和 sid**, 其中 t 和 sid 是获取验证码接口返回的，原样返回给登录接口即可， xcode 是用户输入的验证码。

接口响应示例：

```
{
    "code": "m2",
    "errs": {
        "statusCode": 800,
        "reason": "CaptchaCode required"
    },
    "success": false,
    "user": "AE3413006639"
}
```

这里的 success 字段表明请求是成功还是失败，code 字段的值是用来表示不用类型的错误:

* c0 缺少必填字段 user
* c1 缺少必填字段 pwd
* c2 缺少必填字段 factory
* c3 缺少必填字段 mainServerHost
* c4 用户名或者密码错误
* m0 缺少必填字段 sid
* m1 缺少必填字段 xcode
* m2 缺少必填字段 t
* m3 验证码过期

这里的错误代码只针对美的登录。


## 查询是否需要重新登录接口

POST http://localhost:8000/sessionValid
Content-Type: application/json

请求体示例：

```
{
    "user": "AE3413006639", 
    "factory": "midea", 
}
```

接口响应示例：

```
{
    "status": true
}
```

status 为 false 的时候，表明需要重新登录。注意此接口只针对美的。


## 注意

* 本次修改只针对美的登录接口新增了参数，其他厂家的登录接口保持不变。
* 应该根据 success 字段判断验证码是否获取成功，获取失败时应尝试重新获取，3次以上获取不成功，应提示用户。
* 登录美的时候，如果返回的 code 字段的值是 c4 后者 m3 不要显示“登录失败”，而是显示 “用户名或密码错误” 和 “验证码过期”。
