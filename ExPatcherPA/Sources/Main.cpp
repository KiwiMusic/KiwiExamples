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

int main(int argc, const char * argv[])
{
    // Test : atom parse
    string eval = "cata    toto 4 578 -007 5.4 0.79995 -6.1 .90 -.99 - --9 ..9 99.8.7 44 99.-6 1.123e3 \"vava\" bb \" mojo jojo\" \"12\"  \"-12\" \\a \"non\"\"oui\"  \" jambon ";
    //string eval = "1, 4, 7.9";
    cout << "eval : \"" << eval << "\"" << endl;
    Vector atoms = Atom::parse(eval);
    
    cout << endl << "result :" << endl;
    for (auto atom : atoms)
    {
        if (atom.isLong())
        {
            cout << "- atom long   : " << (long)atom << endl;
        }
        else if (atom.isDouble())
        {
            cout << "- atom double : " << (double)atom << endl;
        }
        else if (atom.isTag())
        {
            cout << "- atom Tag    : \"" << ((sTag)atom)->getName() << "\"" << endl;
        }
    }
    
    return 0;
    
    
    Dico bef;
    bef[Tag::create("b1")] = 1;
    bef[Tag::create("b2")] = 1;
    bef[Tag::create("b3")] = 3;
    Dico dic;
    dic[Tag::create("e1")] = "Pierre et \"Too\" zaza\nzaza";
    dic[Tag::create("e2")] = 12;
    dic[Tag::create("e3")] = "Jack";
    dic[Tag::create("e4")] = 1.3;
    Dico bof;
    bof[Tag::create("e5")] = {9, 8, 7};
    bof[Tag::create("e6")] = "Paul";
    bof[Tag::create("e7")] = bef;
    
    Atom zaza({"zaza", 12.3000, 4, Tag::create("zizi"), true, {1.3f, false, 16l, "zozo"}, 1, 2, 3, dic, "end"});
    cout << zaza << endl << endl << endl;
    
    Dico::value_type p(Tag::create("funk"), "funcku");
    Dico dic2;
    dic2.insert(p);
    Vector& vec = zaza;
    vec.push_back(dic2);
    cout << zaza << endl << endl << endl;
    
    zaza = {bef, dic, bof};
    cout << zaza << endl << endl << endl;
    
    
    sDspDeviceManager manager = make_shared<KiwiPortAudioDeviceManager>();
    if(manager)
    {
        Console::m_dsp_device = manager;
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
        sInstance instance = Instance::create(nullptr, manager, "Instance");
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
