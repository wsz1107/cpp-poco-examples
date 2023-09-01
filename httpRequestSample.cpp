#include <iostream>
#include <string>
#include <Poco/URI.h>
#include <Poco/Path.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

int main(){
    //test web site
    URI uri("http://httpbin.org");
    HTTPClientSession session(uri.getHost(), uri.getPort());
    session.setKeepAlive(true);

    //post body
    Poco::JSON::Object bodyObj;
    bodyObj.set("foo","bar");
    ostringstream ss;
    bodyObj.stringify(ss);
    string body;
    body = ss.str();

    //request header
    //HTTPRequest request(HTTPRequest::HTTP_GET,"/get",HTTPMessage::HTTP_1_1);

    HTTPRequest request(HTTPRequest::HTTP_POST,"/post",HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.add("User-Agent","Mozilla/5.0");
    request.setContentLength(body.length());
    
    session.sendRequest(request) << body;

    //response
    HTTPResponse response;
    istream &page = session.receiveResponse(response);

    string received = "";
    string tmp;
    while(getline(page,tmp)){
        received += tmp + "\n";
    }

    // cout << response.getStatus() << endl;
    cout << received << endl;
    return 0;
}