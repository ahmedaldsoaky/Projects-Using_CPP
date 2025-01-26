#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

const string ClientsFileName = "C:\\Users\\Eng-Ahmed_Fawzy\\Desktop\\MyFile.txt";

struct stClient
{
    string AccountNumber, PinCode, Name, Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

string ConvertRecordToString(stClient& client)
{
    string data = client.Name + "#//#" + client.Phone + "#//#" + client.AccountNumber + "#//#" + client.PinCode + "#//#" + to_string(client.AccountBalance);
    return data;
}


void EditClient(stClient &client)
{
    cout<<"Enter new values: "<<endl;
    cout<<"Name: ";
    cin.ignore();
    getline(cin, client.Name);
    cout<<"Phone: ";
    getline(cin, client.Phone);
    cout<<"Pin Code: ";
    getline(cin, client.PinCode);
    cout<<"Account Balance: ";
    cin>>client.AccountBalance;
}

void PrintClientInfo(stClient client)
{
    cout<<"The following is the client details:\n\n";
    cout<<"------------------------------------------------\n";
    printf("Account Number%-6s: %s"," ", client.AccountNumber.c_str());
    printf("\nPin Code%-12s: %s", " ", client.PinCode.c_str());
    printf("\nName%-16s: %s"," ", client.Name.c_str());
    printf("\nPhone%-15s: %s"," ", client.Phone.c_str());
    printf("\nAccount Balance%-5s: %.2f"," ", client.AccountBalance);
    cout<<"\n------------------------------------------------\n\n\n";
}


bool IsClientExist(string accountNumber, vector<stClient>& clients, int & index)
{
    int cntr = 0;
    for(stClient& client : clients)
    {
        if(client.AccountNumber == accountNumber)
        {
            index = cntr;
            return true;
        }
        cntr++;
    }
    return false;
}

string ClientScreen(string show, string action)
{
    system("cls");
    cout<<"====================================\n";
    cout<<"\t    "<<show<<endl;;
    cout<<"====================================\n";
    string AccountNumber;
    cout<<"Enter Account Number of the client you want to "<< action << ": ";
    cin >> AccountNumber;
    return AccountNumber;
}

void FindClient(vector<stClient>& clients)
{
    string AccountNumber = ClientScreen("Find Client Screen", "find");
    int index;
    bool Found = IsClientExist(AccountNumber, clients, index);
    if(Found)
        PrintClientInfo(clients[index]);
    else
        cout<<"Client not found.\n";
}

void LoadToFile(vector<stClient>& clients)
{
    fstream file;
    file.open(ClientsFileName, ios::out);
    if(file.is_open())
    {
        for(stClient& client : clients)
        {
            if(client.MarkForDelete)
                continue;
            string line = ConvertRecordToString(client);
            file << line << endl;
            file << "====================" << endl;
        }
        file.close();
    }
}


void UpdateClient(vector<stClient> clients)
{
    int index;
    string AccountNumber = ClientScreen("Update Client Screen", "update");
    bool Found  = IsClientExist(AccountNumber, clients, index);
    if(Found)
    {
        PrintClientInfo(clients[index]);
        char sure;
        cout<<"Are you want to edit this account (Y/N)? ";
        cin>>sure;
        if(sure == 'y' || sure == 'Y')
        {
            EditClient(clients[index]);
            LoadToFile(clients);
            cout<<"Account edited successfully"<<endl;
        }
        else
            cout<<"Account is same"<<endl;
    }
    else
        printf("Client with Account Number (%s) Not Found!", AccountNumber.c_str());

}
void BackToMenu()
{
    cout<<"\n\nPress any key to go back to Main Menue...";
    system("pause>0");
}

void DeleteClient(vector<stClient>& clients)
{
    int index;
    string AccountNumber = ClientScreen("Delete Clients Screen", "delete");
    if(IsClientExist(AccountNumber, clients, index))
    {
        PrintClientInfo(clients[index]);
        cout << "Are you sure you want to delete this client? (Y/N): ";
        char ch;
        cin >> ch;
        if(ch == 'Y' || ch == 'y')
        {
            clients[index].MarkForDelete = true;
            cout << "Client with Account Number " << AccountNumber << " deleted successfully." << endl;
            LoadToFile(clients);
        }
    }
    else
        cout << "Client with Account Number " << AccountNumber << " not found." << endl;
}



stClient ConvertLineToRecord(string line, string delimeter = "#//#")
{
    stClient client;
    int pos = line.find(delimeter);
    client.Name = line.substr(0, pos);
    line.erase(0, pos + delimeter.size());
    pos = line.find(delimeter);
    client.Phone = line.substr(0, pos);
    line.erase(0, pos + delimeter.size());
    pos = line.find(delimeter);
    client.AccountNumber = line.substr(0, pos);
    line.erase(0, pos + delimeter.size());
    pos = line.find(delimeter);
    client.PinCode = line.substr(0, pos);
    line.erase(0, pos + delimeter.size());
    client.AccountBalance = stod(line);
    return client;
}

vector<stClient> LoadClientsFromFile(string filename)
{
    fstream file;
    vector<stClient> clients;
    file.open(filename, ios::in);
    if(file.is_open())
    {
        string line;
        while(getline(file, line))
        {
            if(line[0] == '=')
                continue;
            clients.push_back(ConvertLineToRecord(line));
        }
        file.close();
    }
    return clients;
}


void HeaderAddingNewClient()
{
    system("cls");
    cout<<"====================================\n";
    cout<<"\t    Add new Clients Screen\n";
    cout<<"====================================\n";
}

stClient AddClient(vector<stClient>& clients)
{
    stClient client;
    HeaderAddingNewClient();
    cout << "Adding new client:\n\n";
    cout << "Enter Account Number: ";
    cin >> client.AccountNumber;
    int index;
    while(IsClientExist(client.AccountNumber, clients, index))
    {
        printf("\nClient with [%s] is already exists, Enter another Account Number? ", client.AccountNumber.c_str());
        cin >> client.AccountNumber;
    }
    cout << "Enter Pin Code: ";
    cin >> client.PinCode;
    cout << "Enter Client Name: ";
    cin.ignore();
    getline(cin, client.Name);
    cout << "Enter Phone Number: ";
    cin >> client.Phone;
    cout << "Enter Account Balance: ";
    cin >> client.AccountBalance;
    return client;
}

void AddNewClient(vector<stClient>& clients)
{
    HeaderAddingNewClient();
    cout << "Adding new client:\n\n";
    char AddAgain = 'y';
    while(AddAgain == 'y' || AddAgain == 'Y')
    {
        stClient newClient = AddClient(clients);
        clients.push_back(newClient);
        LoadToFile(clients);
        cout << "Client Added Successfully, do you want to add more clients? Y/N?";
        cin >> AddAgain;
    }
}

void Header(int NumberOfClients)
{
    printf("\n\n%-35s Client List (%d) Client(s).\n", " ", NumberOfClients);
    cout<<"-------------------------------------------------------------------------------------------------------\n";
    printf("| Acount Number\t | Pin Code | Client Name \t\t\t| Phone \t\t| Balance\n");
    cout<<"-------------------------------------------------------------------------------------------------------\n\n";
}

void PrintClient(stClient clients)
{
    printf("| %-14s | %-8s | %-34s| %-22s| %-11lf\n", clients.AccountNumber.c_str(), clients.PinCode.c_str(), clients.Name.c_str(), clients.Phone.c_str(), clients.AccountBalance);
}

void PrintClients(vector<stClient> clients)
{
    Header(clients.size());
    for (stClient client : clients)
        PrintClient(client);
    cout<<"\n-------------------------------------------------------------------------------------------------------\n\n";
}
int HeaderMainMenu()
{
    system("cls");
    cout<<"====================================\n";
    cout<<"\t    Main Menu Screen\n";
    cout<<"====================================\n";
    cout<<"\t[1] Show Client List.\n";
    cout<<"\t[2] Add new Client.\n";
    cout<<"\t[3] Delete Client.\n";
    cout<<"\t[4] Update Client Info.\n";
    cout<<"\t[5] Find Client.\n";
    cout<<"\t[6] Exit.\n";
    cout<<"====================================\n";
    cout<<"Choose what do you want to do? [1 to 6]?";
    int choice;
    cin>>choice;
    return choice;
}

int main()
{
    int choice;
    choice = HeaderMainMenu();
    while (choice < 6 && choice > 0)
    {
        vector<stClient> clients;
        clients = LoadClientsFromFile(ClientsFileName);
        switch (choice) {
        case 1:
            PrintClients(clients);
            break;
        case 2:
            AddNewClient(clients);
            break;
        case 3:
            DeleteClient(clients);
            break;
        case 4:
            UpdateClient(clients);
            break;
        case 5:
            FindClient(clients);
            break;
        default:
            break;
        }
        BackToMenu();
        choice = HeaderMainMenu();
    }
}