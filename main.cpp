//
//  main.cpp
//  file
//
//  Created by NYUAD on 06/10/2024.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#define GRAVITY 10.0
#define PI 3.14
using namespace std;
int main() {
    double density(0), height1(0), height2(0), heightDifference(0), length(0), diameter(0), volumeFlowRate(0), viscosity(0), reynoldsNumber, frictionFactor, velocity, energyLoss, pressureDrop;
    char option('0'), fileLine;
    string writeFile, readFile;
    int flag(0);
    
    //loop until the user enters the character 4
    while(option!='4'){
        cout<<"What do you want to do?\n";
        cout<<"1.Enter the parameters needed to calculate the pressure drop\n";
        cout<<"2.Calculate the intermidiate values and the pressure drop\n";
        cout<<"3.See the previously written values in a file\n";
        cout<<"4.Exit the program\n";
        cin>>option;
        
        //the block that runs when the user enters charcter 1
        if(option=='1'){
            int count(0); //a count variable to respond to the users actions
            
            //Accept the lowest height from the user
            while(height1<=0){
                if(count>0){//if the user has entered the while loop more than once
                    cout<<"You have entered an invalid height value, try again\n";
                }
                else{//if this is the first the user enters the while loop
                    cout<<"Enter the highest height of the pipe\n";
                }
                cin>>height1;
                count++;//increment the count variable to track how many times the user entered
            }
            count=0;//this is takes count back to being 0 for the next loop to start from
            
            //Accept the heighst height from the user
            while(height2<=0){
                if(count>0){
                    cout<<"You have entered an invalid height value, try again\n";
                }
                else{
                    cout<<"Enter the lowest height of the pipe\n";
                }
                cin>>height2;
                count++;
            }
            count=0;
            heightDifference=height2-height1;
            
             //Accept the density from the user
            while(density<=0){
                if(count>0){
                    cout<<"You have entered an invalid density value, try again\n";
                }
                else{
                    cout<<"Enter the density of the fluid\n";
                }
                cin>>density;
                count++;
            }
            count=0;
            
            //Accept the length from the user
            while(length<=0){
                if(count>0){
                    cout<<"You have entered an invalid length value, try again\n";
                }
                else{
                    cout<<"Enter the length of the pipe\n";
                }
                cin>>length;
                count++;
            }
            count=0;
            
            //Accept the diameter from the user
            while(diameter<=0){
                if(count>0){
                    cout<<"You have entered an invalid diameter value, try again\n";
                }
                else{
                    cout<<"Enter the diameter of the pipe\n";
                }
                cin>>diameter;
                count++;
            }
            count=0;
            
            //Accept the volume flow rate from the user
            while(volumeFlowRate<=0){
                if(count>0){
                    cout<<"You have entered an invalid volume flow rate value, try again\n";
                }
                else{
                    cout<<"Enter the volume flow rate\n";
                }
                cin>>volumeFlowRate;
                count++;
            }
            count=0;
            
            //Accept the viscosity from the user
            while(viscosity<=0){
                if(count>0){
                    cout<<"You have entered an invalid viscosity value, try again\n";
                }
                else{
                    cout<<"Enter the viscosity of the fluid\n";
                }
                cin>>viscosity;
                count++;
            }
            count=0;
            
            cout<<"You have entered all the parameters needed to calculate the pressure drop\n";
            flag++;
        }
        
        //the block that runs when the user enters character 2
        else if(option=='2'){
            if(flag==0){
                cout<<"You have not entered the values to calculate the pressure drop, go back to option 1 and make sure you enter all the values needed\n";
            }
            else{
                velocity = (4 * volumeFlowRate) / (PI * pow(diameter, 2));//calculate the velocity
                reynoldsNumber = (density * velocity * diameter) / viscosity;//calculate the reynolds number
                if(reynoldsNumber>2000){//check if the flow is laminar
                    cout<<"The reynold's number is greater than 2000, which means the flow of the fluid is turbulant and this program only calculates for the laminar flow\n";
                }
                else{
                    cout<<"Enter the file name you want to write the values in\n";//prompt the user to enter the file name
                    cin>>writeFile;//get the file name from the user
                    frictionFactor=8/reynoldsNumber;
                    energyLoss=(4*frictionFactor*pow(velocity, 2)*length)/diameter;
                    pressureDrop=density * (GRAVITY * heightDifference + energyLoss);
                    ofstream wFile(writeFile, ios::out);//create the output file stream and open the file
                    if(wFile.fail()){//check if the file is opened
                        cout<<"File could not be opend\n";
                        exit(-1);
                    }
                    //write the intermediate and the final pressure drop value in the file
                    wFile<<"Pipe parameters info:\n";
                    wFile<<"\tPressure point 1 height (height1): "<<height1<<endl;
                    wFile<<"\tPressure point 2 height (height2): "<<height2<<endl;
                    wFile<<"\tPipe diameter (diameter): "<<diameter<<endl;
                    wFile<<"\tPipe length (length): "<<length<<endl;
                    wFile<<"\tVolume flow rate (volumeFlowRate): "<<volumeFlowRate<<endl;
                    wFile<<"Fluid Parameters info:\n";
                    wFile<<"\tFluid velocity (velocity): "<<velocity<<endl;
                    wFile<<"\tFluid density (density): "<<density<<endl;
                    wFile<<"\tFluid viscosity (viscosity): "<<viscosity<<endl;
                    wFile<<"\n";
                    wFile<<"\t(Intermediate Parameters)\n";
                    wFile<<"\tReynold's number (reynoldsnumber): "<<reynoldsNumber<<endl;
                    wFile<<"\tFriction loss per kilogram (energyLoss): "<<frictionFactor<<endl;
                    wFile<<"Pressure drop between point 1 and 2: "<<pressureDrop<<endl;
                    cout<<"The intermediate values and the final pressure drop has been successfully written in the file\n";
                    wFile.close();
                }
            }
        }
            
            //the block that runs when the user enters character 3
        else if(option=='3'){
                if(flag==0){
                    cout<<"You have not written in the file to read from, go to option 2 and make sure you write the values in the file\n";
                }
                else{
                    ifstream rFile;
                    while(true){
                        cout<<"Enter the file name you want to read from\n";//prompt the user to enter the file name
                        cin>>readFile;//get the file name
                        rFile.open(readFile, ios::in);//create the output file stream and open it
                        if(rFile.fail()){//check if the file is opened
                            string answer;
                            cout<<"There no file by the file name you provided\n";
                            cout<<"You want to try again? n for no and any other key for yes\n";
                            cin>>answer;
                            if(answer=="n"){
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                    while(!rFile.eof()){//iterate over the line inside the file
                        rFile.get(fileLine);//read the lines of the file one at a time
                        cout<<fileLine;//print the line that is read on the console
                    }
                    rFile.close();
                }
                }
                
            //the block that runs when the users character enters 4
        else if(option=='4'){
                cout<<"You have chose to exit the software\n";
                break;//exit the loop
            }
    
        }
    }

