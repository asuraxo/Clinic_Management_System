/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : WAI CHUNG, SO 
Student ID#: 147446215
Email      : wso8@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    displayPatientTableHeader();
    if (fmt==FMT_TABLE)
    {
        for (i=0; i<max; i++)
        {
            //printf("i: %2d : ", i); //tobe deleted;
            if (patient[i].patientNumber!='\0')
            {
                printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
                displayFormattedPhone(patient[i].phone.number);
                printf(" (%s)", patient[i].phone.description);
                putchar('\n');

            }
        }
        printf("\n");
    }
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection=0;
    do
    {
        printf
        (
            "Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: "
        );
        selection = inputIntRange(0, 2);

        if (selection==1)
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
            clearInputBuffer(); 
        }
    
        else if (selection==2)
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
            clearInputBuffer(); 

        }
        else
        {
            printf("\n");
        }

    }while(selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i=0;
    int newPatientNumber=nextPatientNumber(patient, max);

    for(i=0; i<max; i++)
    {
        if (patient[i].patientNumber==0)
        {
            patient[i].patientNumber=newPatientNumber;
            inputPatient(&patient[i]);
            break;
        }

        else if (newPatientNumber!=0 && i==max-1)
        {
            printf("ERROR: Patient listing is FULL!\n\n");
        }
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int editPatientNumber=0, index=0;

    printf("Enter the patient number: ");
    scanf("%d", &editPatientNumber);
     
    printf("\n");

    index=findPatientIndexByPatientNum(editPatientNumber, patient, max);

    if(index==-1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    
    else
    {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    struct Patient empty={0};

    int delPatientNumber=0, index=0;
    char delOption='\0';
    //char options[3]="yn";

    printf("Enter the patient number: ");
    scanf("%d", &delPatientNumber);
        clearInputBuffer();
    printf("\n");

    index=findPatientIndexByPatientNum(delPatientNumber, patient, max);

    if(index==-1)
    {
        printf("ERROR: Patient record not found!\n");
    }

    else
    {
        printf
            (
                "Name  : %s\n" 
                "Number: %05d\n"
                "Phone : ", patient[index].name, patient[index].patientNumber
            );
            displayFormattedPhone(patient[index].phone.number);
            printf(" (%s)\n\n", patient[index].phone.description);
    
        printf("Are you sure you want to remove this patient record? (y/n): ");

        delOption=inputCharOption("yn");

        if(delOption=='n')
        {
            printf("Operation aborted.\n");
        }
        else if(delOption=='y')
        {
            patient[index]=empty;
            printf("Patient record has been removed!\n");
        }
    }
    printf("\n");
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{    
    int i=0, j=0;
    displayScheduleTableHeader(&data->appointments[0].date, 1);

    sortAppointment(*data);

    for(i=0;i<data->maxAppointments;i++)
    {
        if (data->appointments[i].patientNumber!=0)
        {


            for(j=0;j<data->maxPatient;j++)
            {
                if(data->patients[j].patientNumber==data->appointments[i].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);     
                }
            }



            //displayScheduleData(&data->patients[i], &data->appointments[i], 1);
        }
    }
    printf("\n");
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i=0, j=0;
    struct Date inputDate={0};
    sortAppointment(*data);

    printf("Year        : ");
    scanf("%d", &inputDate.year);
    printf("Month (1-12): ");
    scanf("%d", &inputDate.month);

    int lastDayOfMonth=findLastDayOfMonth(inputDate.year, inputDate.month);

    printf("Day (1-%d)  : ", lastDayOfMonth);
    inputDate.day=inputIntRange(1,lastDayOfMonth);
    printf("\n");
    displayScheduleTableHeader(&inputDate, 0);

    // i=0;
    // while(data->appointments[i+1].patientNumber!=0)
    // {
    //     if(data->appointments[i].date.year==inputDate.year && data->appointments[i].date.month==inputDate.month && data->appointments[i].date.day==inputDate.day)
    //     {    
    //         j=0;
    //         while(data->patients[j].patientNumber!=0)
    //         {
    //             if(data->patients[j].patientNumber==data->appointments[i].patientNumber)
    //             { 
    //                 displayScheduleData(&data->patients[j], &data->appointments[i], 0);
    //             }
    //             j++;
    //         }
    //     }
    //     i++;
    // }

    for (i=0;i<data->maxAppointments;i++)
    {
        if(data->appointments[i].date.year==inputDate.year && data->appointments[i].date.month==inputDate.month && data->appointments[i].date.day==inputDate.day)
        {
            for(j=0;j<data->maxPatient;j++)
            {
                if(data->patients[j].patientNumber==data->appointments[i].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);     
                }
            }
        }
    }

    printf("\n");
}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatient)
{
    struct Appointment inputAppoint={0};
    int checkDuplicated=0, i=0;
    int checkPatientexist=0;

    //Tobe modify
    printf("Patient Number: ");
    scanf("%d", &inputAppoint.patientNumber);
    for(i=0;i<maxPatient;i++)
    {
        if (inputAppoint.patientNumber==patients[i].patientNumber)
        {
            checkPatientexist=1;
        }
    }

    if(checkPatientexist==0)
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }    

    else if(checkPatientexist!=0)
    {
        do
        {
            checkDuplicated=0;
            printf("Year        : ");
            scanf("%d", &inputAppoint.date.year);
            printf("Month (1-12): ");
            inputAppoint.date.month=inputIntRange(1,12);
            int lastDayOfMonth=findLastDayOfMonth(inputAppoint.date.year, inputAppoint.date.month);
            printf("Day (1-%d)  : ", lastDayOfMonth);
            inputAppoint.date.day=inputIntRange(1,lastDayOfMonth);
            printf("Hour (0-23)  : ");
            inputAppoint.time.hour=inputIntRange(0,23);
            printf("Minute (0-59): ");
            inputAppoint.time.min=inputIntRange(0,59);

            for(i=0;i<maxAppointments;i++)
            {
                checkDuplicated+=checkIfTwoAppointmentDuplicated(appointments[i],inputAppoint);
            }
            if (checkDuplicated>0)
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
        }while(checkDuplicated!=0);

        while(inputAppoint.time.hour<START_OPERATION_HOUR
                ||inputAppoint.time.hour>END_OPERATION_HOUR
                ||(inputAppoint.time.hour==END_OPERATION_HOUR && inputAppoint.time.min>END_OPERATION_MIN)
                ||inputAppoint.time.min%APPOINT_MIN_INTERVAL!=0)
        {
            printf
            (
                "ERROR: Time must be between %d:%02d and %d:%02d in %d minute intervals.\n\n",
                START_OPERATION_HOUR,START_OPERATION_MIN,END_OPERATION_HOUR,END_OPERATION_MIN,APPOINT_MIN_INTERVAL
            );
            printf("Hour (0-23)  : ");
            inputAppoint.time.hour=inputIntRange(0,23);
            printf("Minute (0-59): ");
            inputAppoint.time.min=inputIntRange(0,59);
        };

        for(i=0; i<maxAppointments;i++)
        {
            if(appointments[i].date.year==0)
            {
                appointments[i]=inputAppoint;
                printf("\n*** Appointment scheduled! ***\n\n");
     ???           break;
            }
        }
    }
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patient[], int maxPatient)
{
    struct Appointment empty={0};
    struct Date delDate={0};

    int delPatientNumber=0, index=-1, i=0, j=0;
    char delOption='\0';
    //char options[3]={"yn"};
    
    printf("Patient Number: ");
    scanf("%d", &delPatientNumber);
    clearInputBuffer();

    for(i=0;i<maxAppointments;i++)
    {
        if(delPatientNumber==appointments[i].patientNumber)
        {
            printf("Year        : ");
            scanf("%d", &delDate.year);
            printf("Month (1-12): ");
            scanf("%d", &delDate.month);

            int lastDayOfMonth=findLastDayOfMonth(delDate.year, delDate.month);

            printf("Day (1-%d)  : ", lastDayOfMonth);
            delDate.day=inputIntRange(1,lastDayOfMonth);
            index=i;
            printf("\n");

            for(j=0;j<maxPatient;j++)
            {
                if (delPatientNumber==patient[j].patientNumber)
                {
                    printf
                    (
                        "Name  : %s\n" 
                        "Number: %05d\n"
                        "Phone : ", 
                        patient[j].name, patient[j].patientNumber
                    );
                    displayFormattedPhone(patient[j].phone.number);
                    printf(" (%s)\n\n", patient[j].phone.description);
                    break;
                } 
            }
            break;        
        }

    }

    if(index==-1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        printf("Are you sure you want to remove this appointment (y,n): ");
        delOption=inputCharOption("yn");        
        
        if(delOption=='n')
        {
            printf("Operation aborted.\n");
        }
        else if(delOption=='y')
        {
            appointments[index]=empty;
            printf("\nAppointment record has been removed!\n");
        }
    }
    printf("\n");
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNum=0, index=0;
      
    printf("\nSearch by patient number: ");
    scanf("%d", &patientNum);
      
    index=findPatientIndexByPatientNum(patientNum, patient, max);

    if(index==-1)
    {
        printf("\n*** No records found ***\n\n");
    }

    else
    {
        printf
        (
            "\nName  : %s\n" 
            "Number: %05d\n"
            "Phone : ", patient[index].name, patient[index].patientNumber
        );
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)\n\n", patient[index].phone.description);
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNum[PHONE_LEN+1];
    int counter=0, i;
    printf("\nSearch by phone number: ");
    scanf("%[^\n]", &*phoneNum);
      
    printf("\n");
    
    displayPatientTableHeader();
    for (i=0; i<max; i++)
    {
        int result=strcmp(patient[i].phone.number, phoneNum);
        if(result==0)
        {
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            counter++;
        }
    }

    if (counter==0)
    {
        printf("\n*** No records found ***\n\n");
    }

    else
    {
    printf("\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int result=0;
    for(i=0; i<max; i++)
    {
        if (result<=patient[i].patientNumber)
        {
            result=patient[i].patientNumber+1;
        }
    }
    return result;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int index=-1, i;

    for(i=0; i<max; i++)
    {
        if(patientNumber==patient[i].patientNumber)
        {
            index=i;
        }
    }
    return index;
}

//To sort in order according to year, month, day, hour and min
void sortAppointment(struct ClinicData data)
{
    struct Appointment tempAppoint={0};
    //struct Patient tempPatient={0};
    int i=0;

    while(data.appointments[i+1].patientNumber!=0)
    {
        if (data.appointments[i].date.year<data.appointments[i+1].date.year)
        {
            // if (strcmp(data.appointments[i].))
            // {
            //     /* code */
            // }
            
            i++;
        }

        else if(data.appointments[i].date.year>data.appointments[i+1].date.year)
        {
            tempAppoint=data.appointments[i+1];
            data.appointments[i+1]=data.appointments[i];
            data.appointments[i]=tempAppoint;
            
            if (i>0)
            {
                i--;
            }
        }

        else if(data.appointments[i].date.year==data.appointments[i+1].date.year)
        {
            if (data.appointments[i].date.month<data.appointments[i+1].date.month)
            {
                i++;
            }

            else if(data.appointments[i].date.month>data.appointments[i+1].date.month)
            {
                tempAppoint=data.appointments[i+1];
                data.appointments[i+1]=data.appointments[i];
                data.appointments[i]=tempAppoint;
                
                if (i>0)
                {
                    i--;
                }
            }

            else if(data.appointments[i].date.month==data.appointments[i+1].date.month)
            {
                if (data.appointments[i].date.day<data.appointments[i+1].date.day)
                {
                    i++;
                }

                else if(data.appointments[i].date.day>data.appointments[i+1].date.day)
                {

                    tempAppoint=data.appointments[i+1];
                    data.appointments[i+1]=data.appointments[i];
                    data.appointments[i]=tempAppoint;

                    if (i>0)
                    {
                        i--;
                    }
                }
                else if(data.appointments[i].date.day==data.appointments[i+1].date.day)
                {
                    
                    if (data.appointments[i].time.hour<data.appointments[i+1].time.hour)
                    {
                        i++;
                    }
                    
                    else if(data.appointments[i].time.hour>data.appointments[i+1].time.hour)
                    {
                        tempAppoint=data.appointments[i+1];
                        data.appointments[i+1]=data.appointments[i];
                        data.appointments[i]=tempAppoint;

                        if (i>0)
                        {
                            i--;
                        }
                    }
                    else if(data.appointments[i].time.hour==data.appointments[i+1].time.hour)
                    {
                        if (data.appointments[i].time.min<=data.appointments[i+1].time.min)
                        {
                            i++;
                        }

                        else if (data.appointments[i].time.min>data.appointments[i+1].time.min)
                        {
                            tempAppoint=data.appointments[i+1];
                            data.appointments[i+1]=data.appointments[i];
                            data.appointments[i]=tempAppoint;

                            if (i>0)
                            {
                                i--;
                            }
                        }
                    }
                }
            }
        }
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf
        (
            "Patient Data Input\n"
            "------------------\n"
            "Number: %05d\n"
            "Name  : ",
            patient->patientNumber
        );

    inputCString(patient->name, 1, NAME_LEN);
        //clearInputBuffer();//tobe deleted
    putchar('\n');
    inputPhoneData(&patient->phone);
    printf("*** New patient record added ***\n\n");
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int editPhoneSelection=0;
            
    printf
    (
        "Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: "
    );
    editPhoneSelection=inputIntRange(1,4); 

    switch (editPhoneSelection)
    {
    case 1: 
        strcpy(phone->description, "CELL"); 
        printf("\nContact: CELL\n");
        printf("Number : ");
        inputCStringPhone(phone->number, PHONE_LEN,PHONE_LEN);
        printf("\n");
        break;
    case 2: 
        strcpy(phone->description, "HOME");
        printf("\nContact: HOME\n");
        printf("Number : ");
        inputCStringPhone(phone->number, PHONE_LEN,PHONE_LEN);
        printf("\n");
        break;
    case 3: 
        strcpy(phone->description, "WORK"); 
        printf("\nContact: WORK\n");
        printf("Number : ");
        inputCStringPhone(phone->number, PHONE_LEN,PHONE_LEN);
        printf("\n");
        break;
    case 4: 
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "\0");
        printf("\n");
        break;
    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE *fp = NULL;
    int i=0;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (feof(fp)==0 && i<max)
        {
            fscanf
            (
                fp, "%d | %[^|] | %[^|] | ", 
                &patients[i].patientNumber, 
                &*patients[i].name,
                 &*patients[i].phone.description
            );

            if (strcmp(patients[i].phone.description, "TBD")==0)
            {
                *patients[i].phone.number='\0';
            }
            else
            {
                fscanf(fp, "%[^\n]", &*patients[i].phone.number);
            }
            i++;
            //printf("i: %d ; patientNumber: %d\n", i, patients[i].patientNumber);
        }
    }
    fclose(fp);
    return (i);
}

int checkIfTwoAppointmentDuplicated(const struct Appointment recordAppoint, const struct Appointment inputAppoint)
{
    int ifAppointmentDuplicated=0;

    if(recordAppoint.date.year==inputAppoint.date.year)
    {
        if(recordAppoint.date.month==inputAppoint.date.month)
        {
            if(recordAppoint.date.day==inputAppoint.date.day)
            {
                if(recordAppoint.time.hour==inputAppoint.time.hour)
                {
                    if(recordAppoint.time.hour==inputAppoint.time.hour)
                    {
                        ifAppointmentDuplicated=1;
                    }
                }
            }
        }
    }
    return ifAppointmentDuplicated;
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE *fp = NULL;
    int i=0;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (feof(fp)==0 && i<max)
        {
            fscanf
            (
                fp, "%d, %d, %d, %d, %d, %d", 
                &appoints[i].patientNumber, 
                &appoints[i].date.year,
                &appoints[i].date.month,
                &appoints[i].date.day,
                &appoints[i].time.hour,
                &appoints[i].time.min
            );
            i++;
        }
    }
    fclose(fp);
    return (i);
}
