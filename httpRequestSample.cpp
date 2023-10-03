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

int main(int argc, char* argv[]){
    //test web site
    // URI uri("http://httpbin.org");
    URI uri(argv[1]);
    HTTPClientSession session(uri.getHost(), uri.getPort());
    session.setKeepAlive(true);

    //post body
    Poco::JSON::Object bodyObj;
    bodyObj.set("frame_id",100);
    bodyObj.set("up",1);
    bodyObj.set("down",1);
    ostringstream ss;
    bodyObj.stringify(ss);
    string body;
    body = ss.str();

    //request header
    // HTTPRequest request(HTTPRequest::HTTP_GET,"/test",HTTPMessage::HTTP_1_1);

    HTTPRequest request(HTTPRequest::HTTP_POST,"/api/pp",HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.add("User-Agent","Mozilla/5.0");
    request.setContentLength(body.length());
    
    session.sendRequest(request) << body;

    //response
    HTTPResponse response;
    istream &page = session.receiveResponse(response);

    // string received = "";
    // string tmp;
    // while(getline(page,tmp)){
    //     received += tmp + "\n";
    // }

    cout << response.getStatus() << endl;
    // cout << received << endl;
    return 0;
}