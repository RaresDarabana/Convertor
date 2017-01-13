#include <iostream>
#include <fstream>
#include <cstring>

struct database
{
    int code;
    char name[20];
    float matrix[13][13];
    struct additional
    {
        int numberOfElements;
        char legend[13][30];
        int lengths[13];
    }elements;
};

database data[12];

using namespace std;

ifstream fin("values.in");

int unitCode, elementForConversion, valueForConversion, elementToConvert;

void initializations();
bool interaction();
bool firstQuestion();
bool firstAnswer();
bool verifyFirstAnswer(char answer[20]);
bool secondQuestion();
bool secondAnswer();
bool verifySecondAnswer(char answer[20]);
bool thirdQuestion();
bool thirdAnswer();
bool verifyThirdAnswer(int value);
bool fourthQuestion();
bool fourthAnswer();
bool verifyFourthAnswer(char answer[20]);
float printResult();

int main()
{
    initializations();
    bool status=interaction();
    if (status==true)
        {
            cout<<"Conversia a fost un succes!"<<'\n';
        }
        else
        {
            cout<<"Conversia nu s-a putut realiza!"<<'\n';
        }
    return 0;
}

bool interaction()
{
    bool result;
    result=firstQuestion();
    if (result==false)
        {
            cout<<"Nu exista aceasta unitate de masura!"<<'\n';
            return false;
        }
    result=secondQuestion();
    if (result==false)
        {
            cout<<"Aceasta subunitate de masura nu se poriveste domeniului selectat mai sus!"<<'\n';
            return false;
        }
    result=thirdQuestion();
    if (result==false)
        {
            cout<<"Aceasta nu este o valoare numerica!"<<'\n';
            return false;
        }
    result=fourthQuestion();
    if (result==false)
        {
            cout<<"Nu este posibila conversia intre aceste unitati de masura!"<<'\n';
            return false;
        }
    cout<<printResult()<<'\n';
    return true;
}

bool firstQuestion()
{
    cout<<"Ce unitate doriti sa convertiti?"<<'\n';
    bool result=firstAnswer();
    if (result==true)
        {
            return true;
        }
    return false;
}

bool firstAnswer()
{
    char answer[20];
    cin.getline(answer, 19);
    bool result;
    result=verifyFirstAnswer(answer);
    if (result==true)
        {
            return true;
        }
    return false;
}

bool verifyFirstAnswer(char answer[20])
{
    int ok, answerLength, i, j;
    answerLength=strlen(answer);
    for (i=0; i<=10; i++)
        {
            for (j=0, ok=1; j<answerLength && ok; j++)
                {
                    if (answer[j]!=data[i].name[j])
                        {
                            ok=0;
                        }
                }
            if (ok)
                {
                    unitCode=data[i].code;
                    return true;
                }
        }
    return false;
}

bool secondQuestion()
{
    cout<<"Care este unitatea de convertit?"<<'\n';
    bool result=secondAnswer();
    if (result==true)
        {
            return true;
        }
    return false;
}

bool secondAnswer()
{
    char answer[20];
    cin.getline(answer, 19);
    bool result;
    result=verifySecondAnswer(answer);
    if (result==true)
        {
            return true;
        }
    return false;
}

bool verifySecondAnswer(char answer[20])
{
    int ok=0, answerLength, j, i;
    answerLength=strlen(answer);
    for (i=0; i<data[unitCode].elements.numberOfElements; i++)
        {
            if (data[unitCode].elements.lengths[i]==answerLength)
                {
                    for (j=0, ok=1; j<answerLength && ok; j++)
                        {
                            if (answer[j]!=data[unitCode].elements.legend[i][j])
                                {
                                    ok=0;
                                }
                        }
                }
            if (ok)
                {
                    elementForConversion=i;
                    return true;
                }
        }
    return false;
}

bool thirdQuestion()
{
    cout<<"Introduceti o valoare numerica!"<<'\n';
    bool result=thirdAnswer();
    if (result==true)
        {
            return true;
        }
    return false;
}

bool thirdAnswer()
{
    cin>>valueForConversion;
    bool result=verifyThirdAnswer(valueForConversion);
    if (result==true)
        {
            return true;
        }
    return false;
}

bool verifyThirdAnswer(int value)
{
    if (value>0)
        {
            return true;
        }
    return false;
}

bool fourthQuestion()
{
    cout<<"Care este unitatea in care doriti sa convertiti?"<<'\n';
    bool result=fourthAnswer();
    if (result==true)
        {
            return true;
        }
    return false;
}

bool fourthAnswer()
{
    char answer[20];
    cin>>answer;
    bool result;
    result=verifyFourthAnswer(answer);
    if (result==true)
        {
            return true;
        }
    return false;
}

bool verifyFourthAnswer(char answer[20])
{
    int ok=0, answerLength, j, i;
    answerLength=strlen(answer);
    for (i=0; i<data[unitCode].elements.numberOfElements; i++)
        {
            if (data[unitCode].elements.lengths[i]==answerLength)
                {
                    for (j=0, ok=1; j<=answerLength && ok; j++)
                        {
                            if (answer[j]!=data[unitCode].elements.legend[i][j])
                                {
                                    ok=0;
                                }
                        }
                }
            if (ok)
                {
                    elementToConvert=i;
                    return true;
                }
        }
    return false;
}

float printResult()
{
    float result;
    result=valueForConversion*data[unitCode].matrix[elementForConversion][elementToConvert];
    return result;
}
