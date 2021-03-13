/*bool Checkformat(const string command,const char def1,const char def2){
    istringstream input3(command);
    string op3;
    string y1;
    string m1;
    string d1;
    input3>>op3;
    if(input3){
    getline(input3, op3,' ');
    getline(input3, y1,def1);
    getline(input3, m1, def2);
    getline(input3, d1,' ');
    }
    cout<< def1 <<"  qw  "<<def2<<" qw "<<d1<<endl;
    cout<< y1 <<"  qw  "<<m1<<" qw "<<d1<<endl;
    cout<< y1.size() <<"  qw  "<<m1.size()<<" qw "<<d1.size()<<endl;
    if((d1.size()<=2)&&((m1.size())<=2))return true;
    else return false;
}*/
/*
void Reciver(Database& db,const string& command){
    string operation;
    string op2;
    istringstream input(command);
    istringstream input2(command);
    string Event;
    string Datum;
    int y = 0;
    int m = 0;
    int d = 0;
    char def1='-';
    char def2='-';
    bool piz;
    piz = Checkformat(command,def1,def2);
    input>> operation;
    if (operation == "Add") {
        if(input >> y >> def1 >> m >> def2 >> d){
            //cout<<"asd";
            cout<<piz<<"asdad"<<endl;
            if((input.peek()==' ')&&(def1 =='-'&&def2 =='-')){
                if(qval(m,d)){
                    input >> Event;
                    Date date(y,m,d);
                    db.AddEvent(date,Event);
                }
            }
            else{
                input2>> op2;
                input2>> Datum;
                cout<< "Wrong date format: "+Datum<<endl;
            }
        }
        else{
            input2>> op2;
            input2>> Datum;
            cout<< "Wrong date format: "+Datum<<endl;
        }
    }else if (operation == "Del") {
        if(input >> y >> def1 >> m >> def2 >> d){
            if((input.peek()==EOF||input.peek()==' ')&&(def1 =='-'&&def2 =='-')&&Checkformat(command,def1,def2)){
                if(qval(m,d)){
                    input >> Event;
                    Date date(y,m,d);
                    if (Event.size() == 0) db.DeleteDate(date);
                    else db.DeleteEvent(date,Event);
                }
            }
            else{
                input2>> op2;
                input2>> Datum;
                cout<< "Wrong date format: "+Datum<<endl;
            }
        }else{
            input2>> op2;
            input2>> Datum;
            cout<< "Wrong date format: "+Datum<<endl;

        }
    }else if (operation == "Find") {

            if(input >> y >> def1 >> m >> def2 >> d){
                if((input.peek()==EOF)&&(def1 =='-'&&def2 =='-')&&Checkformat(command,def1,def2)){
                    if(qval(m,d)){
                        Date date(y,m,d);
                        db.Find(date);

                    }
                }
                else{
                    input2>> op2;
                    input2>> Datum;
                    cout<< "Wrong date format: "+Datum<<endl;
                }
            }else{
                input2>> op2;
                input2>> Datum;
                cout<< "Wrong date format: "+Datum<<endl;

            }

    } else if (operation == "Print") {
         db.Print();
    }
     else {
        cout<< "Unknown command: "+operation<<endl;

    }
}*/

/*
bool formate_date(istringstream &input,const char& def1,const char& def2){
    string command;
    string y;
    string m;
    string d;
    input.clear();
    input.seekg(0, ios::beg);
    if(input){
        getline(input,command);
        getline(input,y,def1);
        getline(input,m,def2);
        getline(input,d);
    }
    if((d.size()<=2)&&((m.size())<=2))return true;
    else return false;
}
*/

