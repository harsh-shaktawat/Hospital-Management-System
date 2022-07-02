#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<limits.h>
#define SIZE 15
int serType0_index=0;
int serType1_index=0;
/*  The 2 arrays declared below represent problems and their charges for each corresponding index  */
/*  for eg: index=0 ; problem="fever" ; charge"1500"  */
char problems[5][40]={"fever","fracture","kidneystone","diabetes","heartattack"};
char charges[5][40]={"1500","6000","20000","30000","50000"};
struct patient
{
    int PatientNumber;
    int age;
    char gender;
    char FirstName [20];
    char LastName [20];
    char PhoneNumber [10];
    char ResidentialCity [15];
    char Email [30];
    char Doctor [20];
    char Problem [30];
    int ServiceType;

    struct charges
    {
        char TotalCharge [15];
        char TotalDeposited [15];
        char TotalReturn [15];
    }expense;
};
struct patient pat_record[SIZE];
void Initialize(int index){
        pat_record[index].PatientNumber=0;
        pat_record[index].age=0;
        pat_record[index].gender='\0';
        pat_record[index].FirstName[0]='\0';
        pat_record[index].LastName[0]='\0';
        pat_record[index].PhoneNumber[0]='\0';
        pat_record[index].ResidentialCity[0]='\0';
        pat_record[index].Email[0]='\0';
        pat_record[index].Doctor[0]='\0';
        pat_record[index].Problem[0]='\0';
        pat_record[index].ServiceType=-1;
        pat_record[index].expense.TotalCharge[0]='\0';
        pat_record[index].expense.TotalDeposited[0]='\0';
        pat_record[index].expense.TotalReturn[0]='\0';
}
void print_record(int index){
    printf("\nDetails of Patient\n");
    printf("PatientNumber : %d\n", pat_record[index].PatientNumber);
    printf("age : %d\n",pat_record[index].age);
    printf("gender : %c\n", pat_record[index].gender);
    printf("FirstName : %s\n", pat_record[index].FirstName);
    printf("LastName : %s\n",pat_record[index].LastName);
    printf("PhoneNumber : %s\n",pat_record[index].PhoneNumber);
    printf("ResidentialCity : %s\n",pat_record[index].ResidentialCity);
    printf("Email : %s\n",pat_record[index].Email);
    printf("Doctor : %s\n",pat_record[index].Doctor);
    printf("Problem : %s\n",pat_record[index].Problem);
    printf("ServiceType : %d\n",pat_record[index].ServiceType);
    printf("TotalCharge : %s\n",pat_record[index].expense.TotalCharge);
    printf("TotalDeposited : %s\n",pat_record[index].expense.TotalDeposited);
    printf("TotalReturn : %s\n",pat_record[index].expense.TotalReturn);
}
struct patient get_record(){
    struct patient tempRecord;
    printf("enter details:\n");
    printf("enter PatientNumber : ");
    scanf("%d", &tempRecord.PatientNumber);
    printf("enter age :");
    scanf("%d", &tempRecord.age);
    printf("enter gender :");
    scanf(" %c", &tempRecord.gender);
    printf("enter FirstName :");
    scanf("%s",tempRecord.FirstName);
    printf("enter LastName :");
    scanf("%s",tempRecord.LastName);
    printf("enter PhoneNumber : ");
    scanf("%s",tempRecord.PhoneNumber);
    printf("enter ResidentialCity : ");
    scanf("%s",tempRecord.ResidentialCity);
    printf("enter Email : ");
    scanf("%s",tempRecord.Email);
    printf("enter Doctor : ");
    scanf("%s",tempRecord.Doctor);
    printf("enter Problem(fever,fracture,kidneystone,diabetes,heartattack) : ");
    scanf("%s",tempRecord.Problem);
    printf("enter ServiceType :");
    scanf("%d", &tempRecord.ServiceType);
    printf("enter TotalDeposited : ");
    scanf("%s",tempRecord.expense.TotalDeposited);
    int i,flag=1;
    for(i=0;i<5 && flag!=0;i++){
        if(strcmp(tempRecord.Problem,problems[i])==0){
            strcpy(tempRecord.expense.TotalCharge,charges[i]);
            flag=0;
        }
    }
    long long int moneydeposited=atoi(tempRecord.expense.TotalDeposited);
    long long int totalcharge=atoi(tempRecord.expense.TotalCharge);
    if(moneydeposited>=totalcharge){
        itoa(moneydeposited-totalcharge,tempRecord.expense.TotalReturn,10);
    }
    else{
        tempRecord.expense.TotalReturn[0]='\0';
    }
    return tempRecord;
}
void shiftRecord(int start,int end){
    int i;
    for(i=end;i>=start;i--){
        pat_record[i+1]=pat_record[i];
    }
}
void reverse_shiftRecord(int start,int end){
    int i;
    for(i=start;i<end;i++){
        pat_record[i-1]=pat_record[i];
    }
}
void addRecord(){
    struct patient tempRecord=get_record();/*function to take record from user*/
        if(tempRecord.ServiceType==0){
            /*when no record is present*/
            if(pat_record[0].ServiceType==-1){                    
                pat_record[0]=tempRecord;
                serType0_index++;
                serType1_index++;
            }
            else{
                int j,flag=1;
                for(j=0;j<serType0_index && flag!=0;j++){
                    if(tempRecord.PatientNumber<pat_record[j].PatientNumber){
                        shiftRecord(j,serType1_index);
                        pat_record[j]=tempRecord;
                        serType0_index++;
                        serType1_index++;
                        flag=0;
                    }
                }
                if(flag==1){
                    shiftRecord(serType0_index,serType1_index);
                    pat_record[serType0_index]=tempRecord;
                    serType0_index++;
                    serType1_index++;
                }
            }
        }
        else{
            /*when no record is present*/
            if(pat_record[0].ServiceType==-1){
                pat_record[0]=tempRecord;
                serType1_index++;
            }
            else{
                int j,flag=1;
                for(j=serType0_index;j<serType1_index && flag!=0;j++){
                    if(tempRecord.PatientNumber<pat_record[j].PatientNumber){
                        shiftRecord(j,serType1_index);
                        pat_record[j]=tempRecord;
                        serType1_index++;
                        flag=0;
                    }
                }
                if(flag==1){
                    pat_record[serType1_index]=tempRecord;
                    serType1_index++;
                }
            }
        }
}
int searchByPatientNumber(int Patientnum){
    int i,flag=1,ans=-1;
    for(i=0;i<serType1_index && flag!=0;i++){
        if(pat_record[i].PatientNumber==Patientnum){
            ans=i;
            flag=0;
        }
    }
    return ans;
}
int searchByPatientName(char firstname[20],char lastname[20]){
    int i,flag=1,ans=-1;
    for(i=0;i<serType1_index && flag!=0;i++){
        if(strcmp(pat_record[i].FirstName,firstname)==0 && strcmp(pat_record[i].LastName,lastname)==0){
            ans=i;
            flag=0;
        }
    }
    return ans;
}
void searchRecord(){
    int field;
    printf("\nenter the field to search\n(0 for PatientName/1 for PatientNumber)\n");
    scanf("%d", &field);
    if(field==1){
        int Patientnum;
        printf("enter patientnumber\n");
        scanf("%d", &Patientnum);
        int index=searchByPatientNumber(Patientnum);
        if(index!=-1){
            print_record(index);
        }
        else{
            printf("\nRecord not found\n");
        }
    }
    else if(field==0){
        char firstname[20],lastname[20];
        printf("enter first name of patient\n");
        scanf("%s",firstname);
        printf("enter last name of patient\n");
        scanf("%s",lastname);
        int index=searchByPatientName(firstname,lastname);
        if(index!=-1){
            print_record(index);
        }
        else{
            printf("\nRecord not found\n");
        }
    }
    else{
        printf("invalid input field\n");
    }
}
void editRecord_data(int index){
    char ans;
    do{
        char key;
        printf("\nenter the field you want to edit\npress 1(to edit PatientNumber), 2(to edit age), 3(to edit gender),\n");
        printf("4(to edit FirstName), 5(to edit LastName), 6(to edit PhoneNumber), 7(to edit ResidentialCity),\n");
        printf("8(to edit Email), 9(to edit Doctor), 10(to edit Problem), 11(to edit ServiceType),\n");
        printf("12(to edit TotalDeposited amount)\n");
        scanf("%d", &key);
        if(key==1){
            int patientnum;
            printf("enter new PatientNumber\n");
            scanf("%d", &patientnum);
            pat_record[index].PatientNumber=patientnum;
        }
        else if(key==2){
            int age;
            printf("enter new age\n");
            scanf("%d", &age);
            pat_record[index].age=age;
        }
        else if(key==3){
            char gender;
            printf("enter new age\n");
            scanf("%c", &gender);
            pat_record[index].gender=gender;
        }
        else if(key==4){
            char firstname[20];
            printf("enter new first name\n");
            scanf("%s", firstname);
            strcpy(pat_record[index].FirstName,firstname);
        }
        else if(key==5){
            char lastname[20];
            printf("enter new last name\n");
            scanf("%s", lastname);
            strcpy(pat_record[index].LastName,lastname);
        }
        else if(key==6){
            char PhoneNumber[20];
            printf("enter new Phone Number\n");
            scanf("%s", PhoneNumber);
            strcpy(pat_record[index].PhoneNumber,PhoneNumber);
        }
        else if(key==7){
            char ResidentialCity[20];
            printf("enter new ResidentialCity\n");
            scanf("%s",ResidentialCity);
            strcpy(pat_record[index].ResidentialCity,ResidentialCity);
        }
        else if(key==8){
            char Email[20];
            printf("enter new Email\n");
            scanf("%s", Email);
            strcpy(pat_record[index].Email,Email);
        }
        else if(key==9){
            char Doctor[20];
            printf("enter new Doctor\n");
            scanf("%s", Doctor);
            strcpy(pat_record[index].Doctor,Doctor);
        }
        else if(key==10){
            char Problem[20];
            printf("enter new Problem(fever,fracture,kidneystone,diabetes,heartattack)\n");
            scanf("%s", Problem);
            strcpy(pat_record[index].Problem,Problem);
            int i,flag=1;
            for(i=0;i<5 && flag!=0;i++){
                if(strcmp(pat_record[index].Problem,problems[i])==0){
                    strcpy(pat_record[index].expense.TotalCharge,charges[i]);
                    flag=0;
                    }
                }
            long long int totaldeposited=atoi(pat_record[index].expense.TotalDeposited);
            long long int totalcharge=atoi(pat_record[index].expense.TotalCharge);
            if(totaldeposited>=totalcharge){
                itoa(totaldeposited-totalcharge,pat_record[index].expense.TotalReturn,10);
            }
            else{
                pat_record[index].expense.TotalReturn[0]='\0';
            }
            }
        else if(key==11){
            int ServiceType;
            printf("enter ServiceType\n");
            scanf("%d", ServiceType);
            pat_record[index].ServiceType=ServiceType;
        }
        else if(key==12){
            char TotalDeposited[20];
            printf("enter Total amount Deposited\n");
            scanf("%s", TotalDeposited);
            strcpy(pat_record[index].expense.TotalDeposited,TotalDeposited);
            long long int totaldeposited=atoi(pat_record[index].expense.TotalDeposited);
            long long int totalcharge=atoi(pat_record[index].expense.TotalCharge);
            if(totaldeposited>=totalcharge){
                itoa(totaldeposited-totalcharge,pat_record[index].expense.TotalReturn,10);
            }
            else{
                pat_record[index].expense.TotalReturn[0]='\0';
            }
        }
        else{
        printf("invalid field\n");
    }
    printf("want to edit another field\n(y for yes/n for no)\n");
    scanf(" %c", &ans);
    }while(ans!='n');
}
void editRecord(){
    int field;
    printf("\nenter the field to display/edit record\n(0 for PatientName/1 for PatientNumber)\n");
    scanf("%d", &field);
    if(field==1){
        int Patientnum;
        printf("enter patientnumber\n");
        scanf("%d", &Patientnum);
        int index=searchByPatientNumber(Patientnum);
        print_record(index);
        editRecord_data(index);
        printf("New ");
        print_record(index);
    }
    else if(field==0){
        char firstname[20],lastname[20];
        printf("\nenter first name of patient\n");
        scanf("%s",firstname);
        printf("enter last name of patient\n");
        scanf("%s",lastname);
        int index=searchByPatientName(firstname,lastname);
        print_record(index);
        editRecord_data(index);
        printf("New ");
        print_record(index);
    }
    else{
        printf("invalid input field\n");
    }
}
void sort_alphabetically(){
    int i,j,min,k=0;
    int arr[serType1_index];
    for (i=0;i<serType1_index; i++) {
            arr[i] = i;/*Initially the index of the original array are assigned to the 'arr[]'*/
        }
    for(i=0;i<serType1_index-1;i++){
        min=i;
        for(j=i+1;j<serType1_index;j++){/*with the help of 'arr[]' names are being compared*/
            if(strcmp(pat_record[arr[min]].FirstName,pat_record[arr[j]].FirstName)>0){
                min=j;
            }
            else if(strcmp(pat_record[min].FirstName,pat_record[j].FirstName)==0){
                if(strcmp(pat_record[arr[min]].LastName,pat_record[arr[j]].LastName)>0){
                    min=j;
                }
            }
        }
        if(min!=i){/*index of the alphabetical names is placed at the ith index of 'arr[]'*/
            int temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
    }
    printf("\nReocrd of patients in alphabetical order\n");
    for(i=0;i<serType1_index;i++){
        print_record(arr[i]);
    }
}
void listPatient_records(){
    int ans;
    printf("\nEnter the Pattern to print list of patient records\n");
    printf("1 for Records of patients in alphabetical order\n2 for Records of Emergency patients\n3 for Records of O.P.D. patients\n");
    scanf(" %d", &ans);
    if(ans==1){
        sort_alphabetically();
    }
    else if(ans==2){
        int i;
        printf("\nRecord of patients with emergency service\n");
        for(i=serType0_index;i<serType1_index;i++){
            print_record(i);
        }
        }
    else if(ans==3){
        int i;
        printf("\nRecord of patients with O.P.D. service\n");
        for(i=0;i<serType0_index;i++){
            print_record(i);
        }
    }
    else{
        printf("invalid input\n");
    }
}
void deleteRecord(){
    int PatientNum;
    printf("\nenter the Patient number of record to delete\n");
    scanf(" %d", &PatientNum);
    int index=searchByPatientNumber(PatientNum);
    if(index!=-1){
        print_record(index);
        int servicetype=pat_record[index].ServiceType;
        char c;
        printf("\npress y(for yes)/n(for no) to delete the record\n");
        scanf(" %c", &c);
        if(c=='y'){
            reverse_shiftRecord(index+1,serType1_index);
            serType1_index--;
            if(servicetype==0){
                serType0_index--;
                }
            }
            Initialize(serType1_index);
            
        }
    else{
        printf("\nrecord not found\n");
        }
}
void outsiderPatient_data(){
    int i;
    printf("\nPatients residing outside Nagpur\n");
    for(i=0;i<serType1_index;i++){
        if(strcmp(pat_record[i].ResidentialCity,"Nagpur")!=0){
            print_record(i);
        }
    }
}
void FundsReturn_data(){
    int i;
    printf("\nRecords of patient whose money has to be returned\n");
    for(i=0;i<serType1_index;i++){
        if(pat_record[i].expense.TotalReturn[0]!='\0' && pat_record[i].expense.TotalReturn[0]!='0' ){
            print_record(i);
        }
    }
}
void searchRecord_byAge(){
    int key;
    printf("\nenter the range of age of patients\nPress 0(for age 25-40), 1(for age 40+)\n");
    scanf("%d", &key);
    if(key==0){
        int index,count=0;
        printf("\nPatients availing emergency service in age group 25-40 yrs\n");
        for(index=serType0_index;index<serType1_index;index++){
            if(pat_record[index].age<=40 && pat_record[index].age>=25 ){
                print_record(index);
                count++;
            }
        }
        if(count==0){
            printf("no patient\n");
        }
    }
    else if(key==1){
        int index,count=0;
        printf("\nPatients availing emergency service in age group 40+ yrs\n");
        for(index=serType0_index;index<serType1_index;index++){
            if(pat_record[index].age>40){
                print_record(index);
                count++;
            }
        }
        if(count==0){
            printf("No patient\n");
        }
    }
    else{
        printf("\ninvalid input\n");
    }
}
void MaximumMinimum_charges(){
    int i,min_charge=INT_MAX,max_charge=INT_MIN;
    int totalCharge;
    for(i=0;i<serType1_index;i++){
        totalCharge=atoi(pat_record[i].expense.TotalCharge);
        if(totalCharge>max_charge){
            max_charge=totalCharge;
        }
        if(totalCharge<min_charge){
            min_charge=totalCharge;
        }
    }
    printf("\nPatients who are charged maximum amount by hosptial\n");
    for(i=0;i<serType1_index;i++){
        if(atoi(pat_record[i].expense.TotalCharge)==max_charge){
            print_record(i);
        }
    }
    printf("\nPatients who are charged minimum amount by hosptial\n");
    for(i=0;i<serType1_index;i++){
        if(atoi(pat_record[i].expense.TotalCharge)==min_charge){
            print_record(i);
        }
    }
}
void searchRecord_byDoctor(){
    char doctorName[20];
    printf("\nEnter name of doctor whose patients you want to see\n");
    scanf("%s", doctorName);
    int i,count=0;
    printf("\nList of patients taking treatment from doctor %s\n", doctorName);
    for(i=0;i<serType1_index;i++){
        if(strcmp(pat_record[i].Doctor,doctorName)==0){
            print_record(i);
            count++;
        }
    }
    if(count==0){
        printf("\nNo patient is taking treatment from doctor %s\n", doctorName);
    }
}
void viewDoctors(){
    int length=serType1_index;
    char doctors[length][20];
    int i,j;
    for(i=0;i<length;i++){
        strcpy(doctors[i],pat_record[i].Doctor);
    }
    char temp[20];
    for(i=0;i<length-1;i++){
        for(j=i+1;j<length;j++){
            if(strcmp(doctors[i],doctors[j])>0){
                strcpy(temp,doctors[i]);
                strcpy(doctors[i],doctors[j]);
                strcpy(doctors[j],temp);
            }
        }
    }
    temp[0]='\0';
    printf("\ndoctors treating both OPD and Emergency patients\n");
    for(i=0;i<length;i++){
        if(strcmp(temp,doctors[i])!=0){
            printf("%s\n", doctors[i]);
        }
        strcpy(temp,doctors[i]);
    }
    length=serType1_index-serType0_index;
    char emergency_doctors[length][20];
    for(i=0;i<length;i++){
        strcpy(emergency_doctors[i],pat_record[i+serType0_index].Doctor);
    }
    for(i=0;i<length-1;i++){
        for(j=i+1;j<length;j++){
            if(strcmp(emergency_doctors[i],emergency_doctors[j])>0){
                strcpy(temp,doctors[j]);
                strcpy(emergency_doctors[j],emergency_doctors[i]);
                strcpy(emergency_doctors[i],temp);
            }
        }
    }
    temp[0]='\0';
    printf("\ndoctors treating only Emergency patients\n");
    for(i=0;i<length;i++){
        if(strcmp(temp,emergency_doctors[i])!=0){
            printf("%s\n", emergency_doctors[i]);
        }
        strcpy(temp,emergency_doctors[i]);
    }
}
int main(){
    int i;
    for(i=0;i<SIZE;i++){
        Initialize(i); /*initialize each structure*/
    }
    char c='y';
    do{
        int key;
        printf("\nEnter the operation you want to perform\n");
        printf("press 1(to add patient record), 2(Search Patient Record), 3(Edit Patient Record), 4(List record of patients),\n");
        printf("5(Delete Patient Records), 6(Print outsider patient data), 7(to print Maximum and Minimum charge of Treatment)\n");
        printf("8(Funds Return Data), 9(Search patients by Age), 10(Search patients by Doctor), 11(View Doctors)\n");
        scanf("%d", &key);
        if(key==0){
            for(int j=0;j<serType1_index;j++){
                print_record(j);
            }
        }
        else if(key==1){
            int NumOf_Records;
            printf("enter the no of records you want to add\n");
            scanf("%d", &NumOf_Records);
            for(i=0;i<NumOf_Records && serType1_index<SIZE;i++){
                addRecord();/*function for adding record*/
                if(serType1_index==SIZE){
                printf("\nDatabase is full.No empty space to add record\n");
                }
            }
        }
        else if(key==2){
            searchRecord();/*function for adding record*/
        }
        else if(key==3){
            editRecord();
        }
        else if(key==4){
            listPatient_records();
        }
        else if(key==5){
            deleteRecord();
        }
        else if(key==6){
            outsiderPatient_data();
        }
        else if(key==7){
            MaximumMinimum_charges();
        }
        else if(key==8){
            FundsReturn_data();
        }
        else if(key==9){
            searchRecord_byAge();
        }
        else if (key==10){
            searchRecord_byDoctor();
        }
        else if(key==11){
            viewDoctors();
        }
        else{
            printf("invalid input\n");
        }
        printf("\nTo perform another operation press y(for yes)/(n for no)\n");
        scanf(" %c", &c);
    }while(c=='y');    
    return 0;
}
