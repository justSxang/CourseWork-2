#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> facts;
vector<string> rules;
vector<string> newFacts;
vector<string> ruleHolder;

int rem;
int newFact;

void show_();
void addFact();
void addtoFacts(string factString);
bool isFact(string str);
void addRules();
void checkforFacts(string newRule, bool isNewRule);
void genNewFacts();

void show_()
{
    cout << "\nFacts: " << endl;
    for(int i = 0; i < int(facts.size()); i++)
        cout << facts.at(i) << endl;
    
    if(newFact == 1)
    {
        cout << "\nNew Facts: " << endl;
        for(int i = 0; i < int(newFacts.size()); i++)
        {
            cout << newFacts.at(i);
            addtoFacts(newFacts.at(i));
        }
        newFacts.clear();
        newFact = 0;
    }

    cout << "\nRules: " << endl;
    for(int i = 0; i < int(rules.size()); i++)
        cout << rules.at(i) << endl;
}

void addFact()
{
    string sentence;
    cout << "Add Facts: " << endl;
    getline(cin, sentence);

    istringstream iss(sentence);
    string word;
    string combinedString; 

    while (iss >> word) {
        combinedString += word + " "; 
    }

    if (!combinedString.empty()) {
        combinedString.pop_back();
    }
    
    addtoFacts(combinedString);
}

void addtoFacts(string factString)
{
    if(isFact(factString))
    {
        cout << " --This fact already exist." << endl;
    }
    else
    {
        cout << " --will be added as a new Fact." << endl;
        facts.push_back(factString);
    }
}

bool isFact(string str)
{
    if(facts.size() < 1)
    {
        return false;
    }
    else 
    {
        for(int i = 0; i < facts.size(); i++)
        {
            if(str == facts[i])
            {   
                return true;
            }
        }
        return false;
    }
}

void addRules() 
{
    string sentence;
    cout << "Add Rule: ";
    getline(cin, sentence);
    checkforFacts(sentence, true);
}

void checkforFacts(string newRule, bool isNewRule)
{
    string sentence = newRule;
    istringstream iss(sentence);
    vector <string> statements;
    string word;
    string statement;
    string newFact;

    bool then = false;

    iss >> word;
    
    if(word == "if")
    {
        while (iss >> word) 
        {
            if(word == "and")
            {
                statements.push_back(statement);
                statement = "";
                continue;
            }
            cout << statement;
            if(word == "then")
            {
                then = true;
                break;
            }
            statement += word;
            statement += " ";
        }
        if (!statement.empty()) 
        {
            statement.pop_back();
            
        }
        if (statement.back() = ',')
            statement.pop_back();


        if(then)
        {
            while (iss >> word) 
            {
                newFact += word;
                newFact += " ";
            }
            if (!newFact.empty()) 
            {
                newFact.pop_back();
            }
            if(isNewRule)
            {
                rules.push_back(newRule);
                if (statements.size() < 1)
                {
                    if(isFact(statement))
                        newFacts.push_back(newFact);
                    else
                        ruleHolder.push_back(newRule);
                }
                else
                {
                    int j = 0;
                    string s;
                    if(isFact(statement))
                    {
                        for(int i = 0; i < statements.size(); i++)
                        {
                            s = statements.at(i);
                            s.pop_back();
                            if(isFact(s))
                                j++;
                        }
                        cout << j;
                        if (statements.size() == j)
                            newFacts.push_back(newFact);
                        else
                            ruleHolder.push_back(newRule);
                    }
                    else
                        ruleHolder.push_back(newRule);
                }
            }
            else // if not New Rules
            {
                if(statements.size() < 1) // if only 1 if-statement
                {
                    if (isFact(statement)) //check in facts
                    {
                        newFacts.push_back(newFact);
                        rem = 1;
                    }
                    else
                    {
                        for(int i = 0; i < newFacts.size(); i++) //check in new facts
                        {
                            if(statement == newFacts[i])
                            {   
                                newFacts.push_back(newFact);
                                rem = 1;
                            }
                        }
                    }
                }
                else // if more than 1 if-statements
                {
                    int j = 0;
                    string s;
                    if(isFact(statement)) // check last statement in facts
                    {
                        for(int i = 0; i < statements.size(); i++) // other statements
                        {
                            s = statements.at(i);
                            s.pop_back();
                            for(int k = 0; k < newFacts.size(); k++) // check other statements in newFacts
                            {
                                if(s == newFacts[k])   
                                    j++;
                            }
                            if(isFact(s)) // check in facts
                                j++;
                        }
                        if (statements.size() == j++)
                        {
                            newFacts.push_back(newFact);
                            rem = 1;
                        }

                    }
                    
                    else
                    {
                        for(int k = 0; k < newFacts.size(); k++) // check last statement in newFacts
                        {
                            if(statement == newFacts[k])   
                            {
                                for(int i = 0; i < statements.size(); i++) // other statements
                                {
                                    s = statements.at(i);
                                    s.pop_back();
                                    for(int k = 0; k < newFacts.size(); k++) // check other statements in newFacts
                                    {
                                        if(s == newFacts[k])   
                                            j++;
                                    }
                                    if(isFact(s)) // check in facts
                                        j++;
                                }
                                if (statements.size() == j++)
                                {
                                    newFacts.push_back(newFact);
                                    rem = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            cout << "\nPlease add an acceptable rule... with 'if' and 'then'... \n add then...";
            system("pause");
        }
        
    }
    else
    {
        cout << "Please add an acceptable rule... with 'if' and 'then'... \n add if... ";
        system("pause");
    }

}

void genNewFacts()
{
    for(int i = 0; i < int(ruleHolder.size()); i++)
    {
        checkforFacts(ruleHolder.at(i), false);
        if(rem == 1) // remove 
        {
            ruleHolder.erase(ruleHolder.begin() + i);
            rem = 0;
        }
    }
}


////////////////// MAIN ////////////////////////

int main() {

    string choice;
    bool play = true;
    
    
    while(play)
    {
        system("cls");
        show_();
        cout << endl;
        cout << "[1] Add Fact     [2] Add Rules     [3] Generate New Facts     [4] Exit " << endl;
        getline(cin, choice);

        if (choice == "1")
        {
            addFact();
            system("pause");
        }

        else if (choice == "2")
        {
            addRules();
        }

        else if (choice == "3")
        {
            genNewFacts();
            newFact = 1;
        }

        else if (choice == "4")
        {
            system("pause");
            //freeFactArray();
            play = false;
            return 0;
        }

        else
        {
            cout << "\t\tInvalid Input !";
            system("pause");
        }
    }

    return 0;
}