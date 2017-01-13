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

void initializations()
{
    int i=0, j, k;
    for (i=0; i<=9; i++)
        data[i].code=i;

    i=0;
    strcpy(data[i].name, "lungime"); i++;
    strcpy(data[i].name, "arie"); i++;
    strcpy(data[i].name, "volum"); i++;
    strcpy(data[i].name, "timp"); i++;
    strcpy(data[i].name, "viteza"); i++;
    strcpy(data[i].name, "temperatura"); i++;
    strcpy(data[i].name, "masa"); i++;
    strcpy(data[i].name, "energie"); i++;
    strcpy(data[i].name, "presiune"); i++;
    strcpy(data[i].name, "densitate"); i++;
    strcpy(data[i].name, "consum");

    i=0; j=0;
    strcpy(data[i].elements.legend[j], "centimetri"); data[i].elements.lengths[j]=strlen("centimetri"); j++;
    strcpy(data[i].elements.legend[j], "picioare"); data[i].elements.lengths[j]=strlen("picioare"); j++;
    strcpy(data[i].elements.legend[j], "toli"); data[i].elements.lengths[j]=strlen("toli"); j++;
    strcpy(data[i].elements.legend[j], "kilometri"); data[i].elements.lengths[j]=strlen("kilometri"); j++;
    strcpy(data[i].elements.legend[j], "mile"); data[i].elements.lengths[j]=strlen("mile"); j++;
    strcpy(data[i].elements.legend[j], "metri"); data[i].elements.lengths[j]=strlen("metri"); j++;
    strcpy(data[i].elements.legend[j], "milimetri"); data[i].elements.lengths[j]=strlen("milimetri"); j++;
    strcpy(data[i].elements.legend[j], "yarzi"); data[i].elements.lengths[j]=strlen("yarzi");
    data[i].elements.numberOfElements=8;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "ari"); data[i].elements.lengths[j]=strlen("ari"); j++;
    strcpy(data[i].elements.legend[j], "acri"); data[i].elements.lengths[j]=strlen("acri"); j++;
    strcpy(data[i].elements.legend[j], "centimetri patrati"); data[i].elements.lengths[j]=strlen("centimetri patrati"); j++;
    strcpy(data[i].elements.legend[j], "picioare patrate"); data[i].elements.lengths[j]=strlen("picioare patrate"); j++;
    strcpy(data[i].elements.legend[j], "hectari"); data[i].elements.lengths[j]=strlen("hectari"); j++;
    strcpy(data[i].elements.legend[j], "toli patrati"); data[i].elements.lengths[j]=strlen("toli patrati"); j++;
    strcpy(data[i].elements.legend[j], "kilometri patrati"); data[i].elements.lengths[j]=strlen("kilometri patrati"); j++;
    strcpy(data[i].elements.legend[j], "metri patrati"); data[i].elements.lengths[j]=strlen("metri patrati"); j++;
    strcpy(data[i].elements.legend[j], "milimetri patrati"); data[i].elements.lengths[j]=strlen("milimetri patrati"); j++;
    strcpy(data[i].elements.legend[j], "yarzi patrati"); data[i].elements.lengths[j]=strlen("yarzi patrati");
    data[i].elements.numberOfElements=10;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];


    i++; j=0;
    strcpy(data[i].elements.legend[j], "centilitri"); data[i].elements.lengths[j]=strlen("centilitri"); j++;
    strcpy(data[i].elements.legend[j], "centimetri cubi"); data[i].elements.lengths[j]=strlen("centimetri cubi"); j++;
    strcpy(data[i].elements.legend[j], "decilitri"); data[i].elements.lengths[j]=strlen("decilitri"); j++;
    strcpy(data[i].elements.legend[j], "decimetri cubi"); data[i].elements.lengths[j]=strlen("decimetri cubi"); j++;
    strcpy(data[i].elements.legend[j], "picioare cubice"); data[i].elements.lengths[j]=strlen("picioare cubice"); j++;
    strcpy(data[i].elements.legend[j], "galoni"); data[i].elements.lengths[j]=strlen("galoni"); j++;
    strcpy(data[i].elements.legend[j], "toli cubi"); data[i].elements.lengths[j]=strlen("yarzi"); j++;
    strcpy(data[i].elements.legend[j], "litri"); data[i].elements.lengths[j]=strlen("litri"); j++;
    strcpy(data[i].elements.legend[j], "metri cubi"); data[i].elements.lengths[j]=strlen("metri cubi"); j++;
    strcpy(data[i].elements.legend[j], "mililitri"); data[i].elements.lengths[j]=strlen("mililitri"); j++;
    strcpy(data[i].elements.legend[j], "yarzi cubi"); data[i].elements.lengths[j]=strlen("yarzi cubi"); j++;
    data[i].elements.numberOfElements=11;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "saptamani"); data[i].elements.lengths[j]=strlen("saptamani"); j++;
    strcpy(data[i].elements.legend[j], "zile"); data[i].elements.lengths[j]=strlen("zile"); j++;
    strcpy(data[i].elements.legend[j], "ore"); data[i].elements.lengths[j]=strlen("ore"); j++;
    strcpy(data[i].elements.legend[j], "minute"); data[i].elements.lengths[j]=strlen("minute"); j++;
    strcpy(data[i].elements.legend[j], "secunde"); data[i].elements.lengths[j]=strlen("secunde"); j++;
    strcpy(data[i].elements.legend[j], "decisecunde"); data[i].elements.lengths[j]=strlen("decisecunde"); j++;
    strcpy(data[i].elements.legend[j], "centisecunde"); data[i].elements.lengths[j]=strlen("centisecunde");

    data[i].elements.numberOfElements=7;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "centimetri pe secunda"); data[i].elements.lengths[j]=strlen("centimetri pe secunda"); j++;
    strcpy(data[i].elements.legend[j], "picioare pe ora"); data[i].elements.lengths[j]=strlen("picioare pe ora"); j++;
    strcpy(data[i].elements.legend[j], "picioare pe secunda"); data[i].elements.lengths[j]=strlen("picioare pe secunda"); j++;
    strcpy(data[i].elements.legend[j], "kilometri pe ora"); data[i].elements.lengths[j]=strlen("kilometri pe ora"); j++;
    strcpy(data[i].elements.legend[j], "kilometri pe secunda"); data[i].elements.lengths[j]=strlen("kilometri pe secunda"); j++;
    strcpy(data[i].elements.legend[j], "metri pe secunda"); data[i].elements.lengths[j]=strlen("metri pe secunda"); j++;
    strcpy(data[i].elements.legend[j], "metri pe ora"); data[i].elements.lengths[j]=strlen("metri pe ora"); j++;
    strcpy(data[i].elements.legend[j], "mile pe ora"); data[i].elements.lengths[j]=strlen("mile pe ora");
    data[i].elements.numberOfElements=8;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "grade celsius"); data[i].elements.lengths[j]=strlen("grade celsius"); j++;
    strcpy(data[i].elements.legend[j], "grade fahrenheit"); data[i].elements.lengths[j]=strlen("grade fahrenheit"); j++;
    strcpy(data[i].elements.legend[j], "grade kelvin"); data[i].elements.lengths[j]=strlen("grade kelvin"); j++;
    strcpy(data[i].elements.legend[j], "grade rankine"); data[i].elements.lengths[j]=strlen("grade rankine");
    data[i].elements.numberOfElements=4;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "grame"); data[i].elements.lengths[j]=strlen("grame"); j++;
    strcpy(data[i].elements.legend[j], "kilograme"); data[i].elements.lengths[j]=strlen("kilograme"); j++;
    strcpy(data[i].elements.legend[j], "pounds"); data[i].elements.lengths[j]=strlen("pounds"); j++;
    strcpy(data[i].elements.legend[j], "miligrame"); data[i].elements.lengths[j]=strlen("miligrame"); j++;
    strcpy(data[i].elements.legend[j], "uncii"); data[i].elements.lengths[j]=strlen("uncii"); j++;
    strcpy(data[i].elements.legend[j], "tone"); data[i].elements.lengths[j]=strlen("tone");
    data[i].elements.numberOfElements=6;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "jouli"); data[i].elements.lengths[j]=strlen("jouli"); j++;
    strcpy(data[i].elements.legend[j], "kilojouli"); data[i].elements.lengths[j]=strlen("kilojouli"); j++;
    strcpy(data[i].elements.legend[j], "kilowatt pe ora"); data[i].elements.lengths[j]=strlen("kilowatt pe ora");
    data[i].elements.numberOfElements=3;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "atmosfere"); data[i].elements.lengths[j]=strlen("atmosfere"); j++;
    strcpy(data[i].elements.legend[j], "bari"); data[i].elements.lengths[j]=strlen("bari"); j++;
    strcpy(data[i].elements.legend[j], "milimetri coloana de mercur"); data[i].elements.lengths[j]=strlen("milimetri coloana de mercur"); j++;
    strcpy(data[i].elements.legend[j], "megapascali"); data[i].elements.lengths[j]=strlen("megapascali"); j++;
    strcpy(data[i].elements.legend[j], "pascali"); data[i].elements.lengths[j]=strlen("pascali"); j++;
    strcpy(data[i].elements.legend[j], "torri"); data[i].elements.lengths[j]=strlen("torri"); j++;
    data[i].elements.numberOfElements=6;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "grame pe metru cub"); data[i].elements.lengths[j]=strlen("grame pe metru cub"); j++;
    strcpy(data[i].elements.legend[j], "kilograme pe metru cub"); data[i].elements.lengths[j]=strlen("kilograme pe metru cub");
    data[i].elements.numberOfElements=2;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];

    i++; j=0;
    strcpy(data[i].elements.legend[j], "litrii la suta"); data[i].elements.lengths[j]=strlen("litrii la suta"); j++;
    strcpy(data[i].elements.legend[j], "galoni la suta"); data[i].elements.lengths[j]=strlen("galoni la suta");
    data[i].elements.numberOfElements=2;

    for (j=0; j<data[i].elements.numberOfElements; j++)
        for (k=0; k<data[i].elements.numberOfElements; k++)
            fin>>data[i].matrix[j][k];


}
