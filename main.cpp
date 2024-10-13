 /*
 This is a program that calculates the drop
 of an incompressible fluid that is in a laminar flow
 click the run button to run and use it.
 */

//include essential libraries
#include <iostream>//required for cout, cin, and endl functions
#include <fstream>//required for file operation
#include <math.h>//required for pow function
#define GRAVITY 10.0
#define PI 3.14
using namespace std;
int main() {
    //declare and initialize variables
    double density(0), height1(0), height2(0), heightDifference(0), length(0),
    diameter(0), volumeFlowRate(0), viscosity(0), reynoldsNumber, frictionFactor,
    velocity, energyLoss, pressureDrop(0);
    char option('0'), fileLine;
    
    //variables to read the file name from the user
    string writeFile, readFile;
    
    //a variable to track the actions of the user
    int flag(0);
    
    //loop until the user enters the character 4
    while(option!='4'){
        //print out the menu
        cout<<"What are you looking to do?\n";
        cout<<"1.Enter the parameters needed to calculate the pressure drop\n";
        cout<<"2.Calculate the intermediate values and the pressure drop\n";
        cout<<"3.See the previously written values in a file\n";
        cout<<"4.Exit the program\n";
        cin>>option;
        
        //the block that runs when the user enters character 1
        if(option=='1'){
            while(true){
                if(flag>1){//check if the user already entered the variables needed
                    char answer;
                    cout<<"You have already entered the values needed. do you want to enter another set of values? click n for no and any other key for yes\n";
                    cin>>answer;
                    if(answer=='n'){
                        break;
                    }
                }
                
                //Accept height one from the user
                cout<<"Enter height one\n";
                cin>>height1;
                while(height1<=0){//repeat until the user gives a valid height value
                    cout<<"You have entered an invalid height value, try again\n";
                    cin>>height1;
                }
                
                //Accept the height two from the user
                cout<<"Enter height two\n";
                cin>>height2;
                while(height2<=0){//repeat until the user gives a valid height value
                    cout<<"You have entered an invalid height value, try again\n";
                    cin>>height2;
                }
                heightDifference=height2-height1;//calculate the height difference
                
                //Accept the density from the user
                cout<<"Enter the density of the fluid\n";
                cin>>density;
                while(density<=0){//repeat until the user gives a valid density value
                    cout<<"You have entered an invalid density value, try again\n";
                    cin>>density;
                }
                
                //Accept the length from the user
                cout<<"Enter the length of the pipe\n";
                cin>>length;
                while(length<=0){//repeat until the user gives a valid length value
                    cout<<"You have entered an invalid length value, try again\n";
                    cin>>length;
                }
                
                //Accept the diameter from the user
                cout<<"Enter the diameter of the pipe\n";
                cin>>diameter;
                while(diameter<=0){//repeat until the user gives a valid diameter value
                    cout<<"You have entered an invalid diameter value, try again\n";
                    cin>>diameter;
                    
                }
                
                //Accept the volume flow rate from the user
                cout<<"Enter the volume flow rate\n";
                cin>>volumeFlowRate;
                while(volumeFlowRate<=0){//repeat until the user gives a valid volume flow rate value
                    cout<<"You have entered an invalid volume flow rate value, try again\n";
                    cin>>volumeFlowRate;
                }
                
                //Accept the viscosity from the user
                cout<<"Enter the viscosity of the fluid\n";
                cin>>viscosity;
                while(viscosity<=0){//repeat until the user gives a valid viscosity value
                    cout<<"You have entered an invalid viscosity value, try again\n";
                    cin>>viscosity;
                }
                
                cout<<"You have entered all the parameters needed to calculate the pressure drop\n";
                break;
            }
             flag++; //increment the flag by one which confirms the user already selected 1
            }
        
        
        //the block that runs when the user enters character 2
        else if(option=='2'){
            if(flag==0){//check if the user did not select option 1 before selecting option 2
                cout<<"You have not entered the values to calculate the pressure drop, go back to option 1 and make sure you enter all the values needed\n";
            }
            else {
                char answer;
                while(true){
                    if(flag>1){//check if the user already written the values in a file
                        cout<<"You have already entered all the values and written in "<<writeFile<<". do you want to write the same in another file again? click n for no and any other key for yes\n";
                        cin>>answer;
                        if(answer=='n')
                            break;
                    }
                        velocity = (4 * volumeFlowRate) / (PI * pow(diameter, 2));//calculate the velocity
                        reynoldsNumber = (density * velocity * diameter) / viscosity;//calculate the reynolds number
                        if(reynoldsNumber>2000){//check if the flow is laminar
                            cout<<"The reynold's number is greater than 2000, which means the flow of the fluid is turbulant and this program only calculates for the laminar flow\n";
                        }
                        else{
                            cout<<"Enter the file name you want to write the values in including the file extention\n";//prompt the user to enter the file name
                            cin>>writeFile;//get the file name from the user
                            frictionFactor=8/reynoldsNumber;
                            energyLoss=(4*frictionFactor*pow(velocity, 2)*length)/diameter;
                            pressureDrop=density * (GRAVITY * heightDifference + energyLoss);
                            ofstream wFile(writeFile, ios::app);//create the output file stream and open the file
                            if(wFile.fail()){//check if the file is opened
                                cout<<writeFile<<" could not be opend\n";
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
                            wFile<<"\tFriction factor (frictionFactor):"<<frictionFactor<<endl;
                            wFile<<"\tEnergy loss per kilogram (energyLoss): "<<frictionFactor<<endl;
                            wFile<<"Pressure drop between point 1 and 2: "<<pressureDrop;
                            wFile<<"\n";
                            wFile<<"\n";
                            cout<<"The intermediate values and the final pressure drop has been successfully written in "<<writeFile<<endl;
                            wFile.close();
                            cout<<"The calculated pressure difference is: "<<pressureDrop<<endl;
                            flag++;//increment the flag by one which confirms the user has written the values in a file
                            break;
                    }
                }
            }
                }
            
        //the block that runs when the user enters character 3
        else if(option=='3'){
                 
                    ifstream rFile;//create an input file stream
                    while(true){
                        cout<<"Enter the file name you want to read from including the file extention\n";//prompt the user to enter the file name
                        cin>>readFile;//get the file name
                        rFile.open(readFile, ios::in);//open the file
                        if(rFile.fail()){//check if the file is not opened
                            char answer;
                            cout<<readFile<<" does not exist\n";
                            cout<<"You want to try again? n for no and any other key for yes\n";
                            cin>>answer;
                            if(answer=='n'){
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
                
            //the block that runs when the user enters character 4
        else if(option=='4'){
                //confirms the user that the program is terminated
                cout<<"You have chosen to exit the software\n";
                cout<<"Thank you !\n";
                break;//exit the loop
            }
        
        //the block that runs when the user enters any character other than 1, 2, 3, 4
        else{
            cout<<"Invalid input, make sure you select 1 to 4\n";
        }
        }
    }


