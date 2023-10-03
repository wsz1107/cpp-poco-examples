#include <iostream>
#include <string>
#include <Poco/URI.h>
#include <Poco/Path.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>
#include <thread>
#include <chrono>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

void httpPost(int n, string option){
    //test web site
    // URI uri("http://httpbin.org");
    URI uri(option);
    HTTPClientSession session(uri.getHost(), uri.getPort());

    int upP = 0;
    int downP = 0;

    for(int i=0;i<n;i++){
        std::cout<< "prepared to send a post request: " << i+1 <<endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        HTTPRequest request(HTTPRequest::HTTP_POST,"/api/pp",HTTPMessage::HTTP_1_1);
        request.setContentType("application/json");
        request.add("User-Agent","Mozilla/5.0");

        //post body
        Poco::JSON::Object bodyObj;
        bodyObj.set("frame_id",100+i);
        if(i%2 == 0){
            bodyObj.set("up",++upP);
            bodyObj.set("down",downP);
        }else{
            bodyObj.set("up",upP);
            bodyObj.set("down",++downP);
        }
        ostringstream ss;
        bodyObj.stringify(ss);
        string body;
        body = ss.str();
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
    }
}


int main(int argc, char* argv[]){
    int threadWorkCnt = 10;
    int mainWorkCnt = 100;
    
    std::thread thread1(httpPost, threadWorkCnt, argv[1]);

    for(int i=0;i<mainWorkCnt;i++){
        cout << "Main Work No." << i+1 << endl; 
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    thread1.join();

    return 0;
}