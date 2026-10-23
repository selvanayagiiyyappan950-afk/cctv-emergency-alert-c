include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MAX_VEHICLES 100
#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_LOCATION 100
 
// Structure for vehicle information
struct Vehicle {
   char number[20];
   char owner[MAX_NAME];
   char guardian[MAX_NAME];
   char guardianPhone[MAX_PHONE];
   char emergencyPhone[MAX_PHONE];
};
 
// Structure for accident information
struct Accident {
   char vehicleNumber[20];
   char location[MAX_LOCATION];
   char dateTime[50];
};
 
// Function declarations
void addVehicle();
void viewVehicles();
void searchVehicle();
void detectAccident();
void viewAccidentRecords();
 
void saveVehicle(struct Vehicle v);
int findVehicle(char number[], struct Vehicle *v);
void generateAlert(struct Vehicle v, char location[]);
void getCurrentDateTime(char dateTime[]);
 
int main() {
   int choice;
 
   while (1) {
       printf("\n==============================================\n");
       printf(" SMART ACCIDENT DETECTION & ALERT SYSTEM\n");
       printf("==============================================\n");
 
       printf("1. Add Vehicle Details\n");
       printf("2. View Vehicle Details\n");
       printf("3. Search Vehicle\n");
       printf("4. Detect Accident\n");
       printf("5. View Accident Records\n");
       printf("6. Exit\n");
 
       printf("----------------------------------------------\n");
       printf("Enter your choice: ");
       scanf("%d", &choice);
       getchar();
 
       switch (choice) {
           case 1:
               addVehicle();
               break;
 
           case 2:
               viewVehicles();
               break;
 
           case 3:
               searchVehicle();
               break;
 
           case 4:
               detectAccident();
               break;
 
           case 5:
               viewAccidentRecords();
               break;
 
           case 6:
               printf("\nThank you for using the system.\n");
               exit(0);
 
           default:
               printf("\nInvalid choice! Please try again.\n");
       }
   }
 
   return 0;
}
 
// Add a new vehicle
void addVehicle() {
   struct Vehicle v;
 
   printf("\n========== ADD VEHICLE ==========\n");
 
   printf("Enter Vehicle Number: ");
   fgets(v.number, sizeof(v.number), stdin);
   v.number[strcspn(v.number, "\n")] = '\0';
 
   printf("Enter Owner Name: ");
   fgets(v.owner, sizeof(v.owner), stdin);
   v.owner[strcspn(v.owner, "\n")] = '\0';
 
   printf("Enter Guardian Name: ");
   fgets(v.guardian, sizeof(v.guardian), stdin);
   v.guardian[strcspn(v.guardian, "\n")] = '\0';
 
   printf("Enter Guardian Phone Number: ");
   fgets(v.guardianPhone, sizeof(v.guardianPhone), stdin);
   v.guardianPhone[strcspn(v.guardianPhone, "\n")] = '\0';
 
   printf("Enter Emergency Contact Number: ");
   fgets(v.emergencyPhone, sizeof(v.emergencyPhone), stdin);
   v.emergencyPhone[strcspn(v.emergencyPhone, "\n")] = '\0';
 
   saveVehicle(v);
 
   printf("\nVehicle details saved successfully!\n");
}
 
// Save vehicle to file
void saveVehicle(struct Vehicle v) {
   FILE *file;
 
   file = fopen("vehicles.dat", "ab");
 
   if (file == NULL) {
       printf("Error opening vehicle database!\n");
       return;
   }
 
   fwrite(&v, sizeof(struct Vehicle), 1, file);
 
   fclose(file);
}
 
// View all vehicles
void viewVehicles() {
   FILE *file;
   struct Vehicle v;
   int count = 0;
 
   file = fopen("vehicles.dat", "rb");
 
   if (file == NULL) {
       printf("\nNo vehicle records found.\n");
       return;
   }
 
   printf("\n============== VEHICLE DATABASE ==============\n");
 
   while (fread(&v, sizeof(struct Vehicle), 1, file)) {
       count++;
 
       printf("\nVehicle %d\n", count);
       printf("Vehicle Number       : %s\n", v.number);
       printf("Owner Name           : %s\n", v.owner);
       printf("Guardian Name        : %s\n", v.guardian);
       printf("Guardian Phone       : %s\n", v.guardianPhone);
       printf("Emergency Contact    : %s\n", v.emergencyPhone);
   }
 
   if (count == 0)
       printf("No records available.\n");
 
   fclose(file);
}
 
// Search vehicle
void searchVehicle() {
   char number[20];
   struct Vehicle v;
 
   printf("\n========== SEARCH VEHICLE ==========\n");
 
   printf("Enter Vehicle Number: ");
   fgets(number, sizeof(number), stdin);
   number[strcspn(number, "\n")] = '\0';
 
   if (findVehicle(number, &v)) {
       printf("\nVehicle Found!\n");
       printf("----------------------------------\n");
       printf("Vehicle Number    : %s\n", v.number);
       printf("Owner Name        : %s\n", v.owner);
       printf("Guardian Name     : %s\n", v.guardian);
       printf("Guardian Phone    : %s\n", v.guardianPhone);
       printf("Emergency Phone   : %s\n", v.emergencyPhone);
   } else {
       printf("\nVehicle not found in database.\n");
   }
}
 
// Find vehicle in database
int findVehicle(char number[], struct Vehicle *v) {
   FILE *file;
 
   file = fopen("vehicles.dat", "rb");
 
   if (file == NULL)
       return 0;
 
   while (fread(v, sizeof(struct Vehicle), 1, file)) {
       if (strcmp(v->number, number) == 0) {
           fclose(file);
           return 1;
       }
   }
 
   fclose(file);
   return 0;
}
 
// Accident detection
void detectAccident() {
   int accident;
   char number[20];
   char location[MAX_LOCATION];
   char dateTime[50];
   struct Vehicle v;
   struct Accident a;
   FILE *file;
 
   printf("\n========== ACCIDENT DETECTION ==========\n");
 
   /*
      In the real system, this value would come
      from CCTV + image processing/AI.
   */
 
   printf("Has an accident been detected?\n");
   printf("1. YES\n");
   printf("2. NO\n");
   printf("Enter choice: ");
   scanf("%d", &accident);
   getchar();
 
   if (accident != 1) {
       printf("\nNo accident detected.\n");
       return;
   }
 
   printf("\nAccident detected!\n");
 
   /*
      In the real system, the number plate would
      be obtained automatically using OCR.
   */
 
   printf("Enter detected vehicle number: ");
   fgets(number, sizeof(number), stdin);
   number[strcspn(number, "\n")] = '\0';
 
   printf("Enter accident location: ");
   fgets(location, sizeof(location), stdin);
   location[strcspn(location, "\n")] = '\0';
 
   // Search vehicle database
   if (findVehicle(number, &v)) {
 
       getCurrentDateTime(dateTime);
 
       // Store accident record
       strcpy(a.vehicleNumber, number);
       strcpy(a.location, location);
       strcpy(a.dateTime, dateTime);
 
       file = fopen("accidents.dat", "ab");
 
       if (file != NULL) {
           fwrite(&a, sizeof(struct Accident), 1, file);
           fclose(file);
       }
 
       printf("\n==========================================\n");
       printf("          ACCIDENT CONFIRMED\n");
       printf("==========================================\n");
 
       printf("Vehicle Number    : %s\n", v.number);
       printf("Owner             : %s\n", v.owner);
       printf("Guardian          : %s\n", v.guardian);
       printf("Guardian Phone    : %s\n", v.guardianPhone);
       printf("Emergency Phone   : %s\n", v.emergencyPhone);
       printf("Location          : %s\n", location);
       printf("Date & Time       : %s\n", dateTime);
 
       generateAlert(v, location);
 
   } else {
       printf("\nVehicle number not found in database.\n");
       printf("Emergency alert could not be linked to a registered vehicle.\n");
   }
}
 
// Generate emergency alert
void generateAlert(struct Vehicle v, char location[]) {
 
   printf("\n==========================================\n");
   printf("          EMERGENCY ALERT\n");
   printf("==========================================\n");
 
   printf("\nSMS TO GUARDIAN\n");
   printf("------------------------------------------\n");
   printf("To: %s\n", v.guardianPhone);
 
   printf("Message:\n");
   printf("ACCIDENT ALERT! An accident involving ");
   printf("vehicle %s has been detected.\n", v.number);
   printf("Location: %s\n", location);
   printf("Please contact emergency services immediately.\n");
 
   printf("\nSMS TO EMERGENCY CONTACT\n");
   printf("------------------------------------------\n");
   printf("To: %s\n", v.emergencyPhone);
 
   printf("Message:\n");
   printf("EMERGENCY: Accident detected for vehicle %s.\n",
          v.number);
   printf("Location: %s\n", location);
 
   printf("\nCALL INITIATED TO GUARDIAN: %s\n",
          v.guardianPhone);
 
   printf("CALL INITIATED TO EMERGENCY CONTACT: %s\n",
          v.emergencyPhone);
 
   printf("\nEmergency alert process completed.\n");
}
 
// Get current date and time
void getCurrentDateTime(char dateTime[]) {
   time_t currentTime;
   struct tm *localTime;
 
   currentTime = time(NULL);
   localTime = localtime(&currentTime);
 
   strftime(dateTime, 50,
            "%d-%m-%Y %H:%M:%S",
            localTime);
}
 
// View accident records
void viewAccidentRecords() {
   FILE *file;
   struct Accident a;
   int count = 0;
 
   file = fopen("accidents.dat", "rb");
 
   if (file == NULL) {
       printf("\nNo accident records found.\n");
       return;
   }
 
   printf("\n========== ACCIDENT RECORDS ==========\n");
 
   while (fread(&a, sizeof(struct Accident), 1, file)) {
       count++;
 
       printf("\nAccident %d\n", count);
       printf("Vehicle Number : %s\n", a.vehicleNumber);
       printf("Location       : %s\n", a.location);
       printf("Date & Time    : %s\n", a.dateTime);
   }
 
   fclose(file);
}