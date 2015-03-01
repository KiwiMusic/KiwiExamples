//
//  main.cpp
//  example
//
//  Created by Guillot Pierre on 01/02/2015.
//  Copyright (c) 2015 Kiwi. All rights reserved.
//

#include <iostream>

#include "../../KiwiModules/KiwiModules.h"

using namespace Kiwi;


static void post_atom(Atom const& atom)
{
    if(atom.isBool())
    {
        if((bool)atom)
            cout << "true";
        else
            cout << "false";
    }
    else if(atom.isLong())
    {
        cout << (long)atom;
    }
    else if(atom.isDouble())
    {
        cout << (double)atom;
    }
    else if(atom.isTag())
    {
        cout << ((sTag)atom)->getName();
    }
    else if(atom.isVector())
    {
        Vector const& vec = atom;
        cout << "{";
        for(Vector::size_type i = 0; i < vec.size();)
        {
            post_atom(vec[i]);
            if(++i != vec.size())
            {
                cout << ", ";
            }
        }
        cout << "}";
    }
    else if(atom.isDico())
    {
        Dico const& dico = atom;
        cout << "{";
        for(auto it = dico.begin(); it != dico.end();)
        {
            cout << it->first->getName() << " : ";
            post_atom(it->second);
            if(++it != dico.end())
            {
                cout << ", ";
            }
        }
        cout << "}";
    }
    else
    {
        cout << "Undefinded";
    }
}

int main(int argc, const char * argv[])
{
    Dico dic;
    dic[Tag::create("e1")] = "Pierre";
    dic[Tag::create("e2")] = 12;
    dic[Tag::create("e3")] = "Jack";
    dic[Tag::create("e4")] = 1.3;
    dic[Tag::create("e5")] = {9, 8, 7};
    dic[Tag::create("e6")] = "Paul";
    
    Atom zaza({"zaza", 12.3, 4, Tag::create("zizi"), true, {1.3f, false, 16l, "zozo"}, 1, 2, 3, dic, "end"});
    post_atom(zaza);
    cout << endl;
    
    Dico::value_type p(Tag::create("funk"), "funcku");
    Dico dic2;
    dic2.insert(p);
    Vector& vec = zaza;
    vec.push_back(dic2);
    post_atom(zaza);
    cout << endl;
    
    return 0;
    
    
    
    
    sDspDeviceManager manager = make_shared<KiwiPortAudioDeviceManager>();
    if(manager)
    {
        Console::device = manager;
        manager->setSampleRate(44100);
        manager->setVectorSize(64);
        cout << "Port Audio Device : Sample Rate (" << manager->getSampleRate() << ") Vector Size (" << manager->getVectorSize() << ")" << endl;

       
        while(1)
        {
            string input;
            cout << "Command : ";
            getline(cin, input);
            cout << input << endl;
            try
            {
                if(!Console::receive(input))
                {
                    return 0;
                }
            }
            catch(exception& e)
            {
                cout << "Error " << e.what() << endl;
            }
        }
        
        return 0;
        sInstance instance = Instance::create(manager, "Instance");
        if(instance)
        {
            try
            {
                instance->start();
            }
            catch (exception& e)
            {
                cout << e.what() << endl;
            }
            
            Dico dico;
            sPatcher page = instance->createPatcher(dico);
            if(page)
            {
                try
                {
                    page->DspChain::start();
                }
                catch(exception& e)
                {
                    cout << "Error " << e.what() << endl;
                }
                
                while(1)
                {
                    vector<Atom> inputs, results;
                    string input, word, command;
                    cout << "Patcher command : ";
                    getline(cin, input);
                    
                    istringstream iss(input);
                    iss >> command;
                    
                    while(iss >> word)
                    {
                        cout << word << " ";
                    }

                    try
                    {
                        if(command == "exit")
                        {
                            return 0;
                        }
                        else if(command == "create")
                        {
                            
                        }
                        else if(command == "remove")
                        {
                            
                        }
                        else if(command == "set")
                        {
                            
                        }
                        else if(command == "get")
                        {
                            
                        }
                        else
                        {
                            Console::post("Unknown command : " + command);
                        }
                        
                    }
                    catch(exception& e)
                    {
                        cout << "Error " << e.what() << endl;
                    }
                }
            }
        }
    }
    return 0;
}
