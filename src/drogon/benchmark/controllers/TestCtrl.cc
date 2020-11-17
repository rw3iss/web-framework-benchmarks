#include "TestCtrl.h"
void TestCtrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    //write your application logic here
    // auto resp=HttpResponse::newHttpResponse();
    // resp->setStatusCode(k200OK);
    // resp->setContentTypeCode(CT_TEXT_HTML); // CT_TEXT_PLAIN, CT_APPLIATION_JSON
    // resp->setBody("Hello World!");

    Json::Value ret;
    ret["username"]="username";
    ret["name"]="Ryan";
    auto resp=HttpResponse::newHttpJsonResponse(ret);

    callback(resp);
}