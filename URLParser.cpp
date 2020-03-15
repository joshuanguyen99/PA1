/*
Author: Joshua Nguyen
Date: 1/30/2020
Project: URL Parser
*/
#include <iostream>
#include <string>
#include "version.h"

using namespace std;

// Function prototypes
bool isValidProtocol(string);
bool isValidPortNum(int);
bool isValidHost(string);
bool isValidFilePath(string);

static double versionNum = 1.2; // Version Number

int main()
{
    version v; // version
    v.displayVersion();
    cout << versionNum << endl;
    string url; // url
    bool validProtocol; // Validity of protocol
    bool validPortNum = true; //True by default, validity of port number
    bool validHost; // Validity of host
    bool containsParameter = false; 
    bool validFilePath; // Validity of file path
    bool startOver = true; // Starting over variable
    
    while(startOver)
    {
        // Prompts user to enter a url
        cout << "Enter Url: ";
        cin >> url;
    
        int index = url.find("://"); // index of "://"
    
        // If the url does not conatin "://" then it is not a valid url
        if(index == -1)
        {
            cout << "Invalid Url with following erroneous components: " << endl;
            cout << "Protocol:\t" << url << " is not a valid protocol" << endl;

            string yesNo; // Yes or no
            cout << "\nWould you like to enter another URL? (Press y for yes) ";
            cin >> yesNo;
            if(yesNo == "y")
            {
                continue;
            }
            else
            {
                exit(EXIT_FAILURE);
            }
            
        }
    
        string protocol = url; // Protocol
        protocol.resize(index); // Takes the protocol part of the original url
        validProtocol = isValidProtocol(protocol); // Checks to see if protocol is valid
    
        string newUrl = url; // Temporary url that is being erased from
        newUrl.erase(0, index + 3); // Erases protocol from newUrl
    
        int index2 = newUrl.find(":"); // To find if there is a port
        int portNum = -1;
    
        if(index2 != -1)
        {
            string port = newUrl; // String to hold port
        
            int index3 =  newUrl.find("/"); // Finds the end of port
        
            // Erases the url until it only holds the port
            port.erase(index3, port.length() -1);
            port.erase(0, index2 + 1);
        
            newUrl.erase(index2, index3 - index2); // Erases port from newUrl
        
            portNum = stoi(port);
            validPortNum = isValidPortNum(portNum); // Checks to see if port number is valid
        }
    
        string firstPart = newUrl; // first part of domain
        string secondPart; // second part of domain
        string host; // host
    
        // Takes out everything but first part of the domain
        int firstDot = newUrl.find("."); // first dot in domain
        firstPart.erase(firstDot, firstDot - newUrl.length());
    
    
        newUrl.erase(0, firstDot + 1); // Updates newUrl
    
        // Takes out everything but second part of the domain
        secondPart = newUrl;
        int secondDot = newUrl.find("."); // second dot in domain
        secondPart.erase(secondDot, secondDot - newUrl.length());
    
        newUrl.erase(0, secondDot + 1); // Updates newUrl
    
        // Takes out everything but the host
        host = newUrl;
        int endOfHost = newUrl.find("/"); // End of host
        host.erase(endOfHost, endOfHost - newUrl.length());
    
        newUrl.erase(0, endOfHost); // Updates newUrl
    
        validHost = isValidHost(host); // Checks to see if hostis valid
    
        int indexOfParameter = newUrl.find("?"); // Index of "?"
        string parameter = ""; // Parameter
        if(indexOfParameter != -1)
        {
            // Finds the parameter and updates the newUrl
            parameter = newUrl;
            parameter.erase(0, indexOfParameter + 1);
            newUrl.erase(indexOfParameter, parameter.length() + 1);
        }
        
        string filePath = newUrl; // The file path
        validFilePath = isValidFilePath(filePath); //Checks to see if file path is valid
    
        // Putting all three parts again to make domain
        string domain = ""; // Domain
        domain.append(firstPart);
        domain.append(".");
        domain.append(secondPart);
        domain.append(".");
        domain.append(host);
    
        if(validProtocol == true && validPortNum == true && validHost == true && validFilePath == true)
        {
            cout << "Protocol:\t " << protocol << endl;
            cout << "Domain:\t\t " << domain << endl;
            // If there is a port number
            if(portNum != -1)
            {
                cout << "Port:\t\t " << portNum << endl;
            }
            cout << "File Path:\t " << filePath << endl;
            // If there is a parameter
            if(parameter != "")
            {
                cout << "Parameters:\t " << parameter << endl;
            }
        }
        else
        {
            cout << "Invalid Url with following erroneous components: " << endl;
            if(validProtocol == false)
            {
                cout << protocol << " is not a valid protocol" << endl;
            }
            if(validPortNum == false)
            {
                cout << "port number must be in between 1 and 65535" << endl;
            }
            if(validHost == false)
            {
                cout << host << " is an invalid domain name" << endl;
            }
            if(validFilePath == false)
            {
                cout << "file path must have a .html or .htm at the end" << endl;
            }
        }
        string yesOrNo;
        cout << "\nWould you like to enter another URL? (Press y for yes) ";
        cin >> yesOrNo;
        if(yesOrNo == "y")
        {
            startOver = true;
        }
        else
        {
            startOver = false;
        }
    }

    return 0;
} // end of main

/* This function makes sure that the protocol is either https, http, ftps,
or ftp, returns false otherwise
*/
bool isValidProtocol(string protocol)
{
    // Protocol has to be https, http, ftps, or ftp to be valid
    if(protocol == "https" || protocol == "http" || protocol == "ftps" || protocol == "ftp")
    {
        return true;
    }
    return false;
} // end of isValidProtocol

/* This function makes sure that the port number is within the range of 
1 and 65535, returns false otherwise
*/
bool isValidPortNum(int portNum)
{
    // Port number has to be between 1 and 65535 to be valid
    if(portNum >= 1 && portNum <= 65535)
    {
        return true;
    }
    return false;
} // end of isValidPortNum

/* This function makes sure that the host is either com, net, gov, biz,
or edu, returns false otherwise
*/
bool isValidHost(string host)
{
    // Host has to be com, net, gov, biz, or edu to be valid
    if(host == "com" || host == "net" || host == "gov" || host == "biz" || host == "edu")
    {
        return true;
    }
    return false;
} // end of isValidHost

/* This function makes sure that the file path has a .html or .htm,
returns false otherwise
*/
bool isValidFilePath(string filePath)
{
    if(filePath.find(".html") != -1 || filePath.find(".htm") != -1)
    {
        return true;
    }
    return false;
} // end of isValidFilePath
