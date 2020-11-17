#include "MainCtrl.h"
void MainCtrl::getJson(const HttpRequestPtr &req,
             std::function<void (const HttpResponsePtr &)> &&callback) const
{
    LOG_DEBUG<<"Main getJson";

    //Verify the validity of the token, etc.
    //Read the database or cache to get user information
    Json::Value ret;
    ret["username"]="username2";
    ret["name"]="Ryan";
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
