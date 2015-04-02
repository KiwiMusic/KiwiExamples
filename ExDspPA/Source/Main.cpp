//
//  main.cpp
//  PortAudioExample
//
//  Created by Guillot Pierre on 19/02/2015.
//  Copyright (c) 2015 Kiwi. All rights reserved.
//

#include "../../KiwiModules/KiwiModules.h"

using namespace Kiwi;

int main(int argc, const char * argv[])
{
    cout << "Start" << endl;
    shared_ptr<DspDeviceManager> manager = make_shared<KiwiPortAudioDeviceManager>();
    if(manager)
    {
        manager->start();
        manager->setInputDevice("Built-in");
        manager->setOutputDevice("Built-in");
        manager->setSampleRate(44100);
        manager->setVectorSize(64);
        /*
        vector<string> names;
        cout << "Available Drivers : ";
        manager->getAvailableDrivers(names);
        for(ulong i = 0; i < names.size(); i++)
        {
            cout << names[i] << ", ";
        }
        
        cout << endl << "Available Input Devices : ";
        manager->getAvailableInputDevices(names);
        for(ulong i = 0; i < names.size(); i++)
        {
            cout << names[i] << ", ";
        }
        
        cout << endl << "Available Output Devices : ";
        manager->getAvailableOutputDevices(names);
        for(ulong i = 0; i < names.size(); i++)
        {
            cout << names[i] << ", ";
        }
        vector<ulong> sizes;
        cout << endl << "Available SampleRate : ";
        manager->getAvailableSampleRates(sizes);
        for(ulong i = 0; i < sizes.size(); i++)
        {
            cout << sizes[i] << ", ";
        }
        
        cout << endl << "Available VectorSize : ";
        manager->getAvailableVectorSizes(sizes);
        for(ulong i = 0; i < sizes.size(); i++)
        {
            cout << sizes[i] << ", ";
        }
        
        cout << endl << endl << "Current configuration : " << endl;
        cout << "Driver : " << manager->getDriverName() << endl;
        cout << "Devices : " << manager->getInputDeviceName() << ", " << manager->getOutputDeviceName() << endl;
        cout << "Ioputs : " << manager->getNumberOfInputs() << ", " << manager->getNumberOfOutputs() << endl;
        cout << "Sr & Vs : " << manager->getSampleRate() << ", " << manager->getVectorSize() << endl << endl;
        */
        sDspContext ctxt = make_shared<DspContext>(manager);
        if(ctxt)
        {
            try
            {
                ctxt->start();
            }
            catch (exception& e)
            {
                cout << e.what() << endl;
            }
            sDspChain chain = make_shared<DspChain>(ctxt);
            if(chain)
            {
                ctxt->add(chain);
                sDspNode Noise = make_shared<DspNoise::White>(chain);
                sDspNode Dac = make_shared<DspDac>(chain, vector<ulong>{(ulong)1, (ulong)2});
                sDspLink cnectLeft = make_shared<DspLink>(chain, Noise, 0, Dac, 0);
                sDspLink cnectRight = make_shared<DspLink>(chain, Noise, 0, Dac, 1);
                chain->add(Noise);
                chain->add(Dac);
                
                
                
                chain->add(cnectRight);
                chain->add(cnectLeft);
                chain->remove(cnectRight);
                chain->remove(cnectLeft);
                
                
                shared_ptr<DspPhasor<DspScalar>> Phasor = make_shared<DspPhasor<DspScalar>>(chain, 220.);
                shared_ptr<DspOscillator<DspScalar>> Osc = make_shared<DspOscillator<DspScalar>>(chain, 0);
                chain->add(Phasor);
                chain->add(Osc);
                cnectRight = make_shared<DspLink>(chain, Phasor, 0, Dac, 1);
                chain->add(cnectRight);
                cnectLeft = make_shared<DspLink>(chain, Osc, 0, Dac, 0);
                chain->add(cnectLeft);
                
                try
                {
                    chain->start();
                }
                catch(exception& e)
                {
                    cout << e.what() << endl;
                    return 0;
                }
                
                int zaza = 100;
                while(zaza--)
                {
                    this_thread::sleep_for(chrono::milliseconds(25));
                    //cout << ctxt->getCPU() << ", ";
                    Phasor->setFrequency(zaza * 22.);
                    Osc->setFrequency((120 - zaza) * 22.);
                }
            }
        }
    }
    cout << "End" << endl;
    
    return 0;
}
