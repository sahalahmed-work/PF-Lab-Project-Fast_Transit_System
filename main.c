#include <stdio.h>
#include <string.h>
#define BASE_FEE 30000.0
#define RATE_PER_KM 500.0
#define SEMESTER_MONTHS 6.0
// Route Details
struct Route {
    int id;
    char name[60];
    float distance; 
    char busNumber[20]; 
};
// Student Details
struct Student {
    char name[50];
    char email[50];
    char contact[20];
    int routeChoice;
    int tier;         
    int paymentMode;  
    float finalFare;
    char assignedBus[20];
};

void printRouteStops(int id) {
    printf("\n----------------------------------------\n");
    printf("         STOPS FOR ROUTE ID [%d]        \n", id);
    printf("----------------------------------------\n");
    if (id == 1) {
        printf("1. Malir Cantt Askari-V (Start)\n");
        printf("2. Check Post - 5\n");
        printf("3. Check Post - 6\n");
        printf("4. Tank Chowk\n");
        printf("5. FAST NU (Destination)\n");
    } else if (id == 2) {
        printf("1. Sector - J Malir Cantt (Start)\n");
        printf("2. Sector - G Malir Cantt\n");
        printf("3. Malir Cantt Phase-I\n");
        printf("4. Sector - H Malir Cantt\n");
        printf("5. Tariq Bin Zaid Society\n");
        printf("6. Security Printing Press\n");
        printf("7. FAST NU (Destination)\n");
    } else if (id == 11) {
        printf("1. Soldier Bazar (Start)\n");
        printf("2. Guru Mandir\n");
        printf("3. Islamia College\n");
        printf("4. Stadium Road\n");
        printf("5. FAST NU (Destination)\n");
    } else if (id == 12) {
        printf("1. Khudadad Colony (Start)\n");
        printf("2. Kashmir Road\n");
        printf("3. Sir Syed Road\n");
        printf("4. Khalid Bin Waleed Road\n");
        printf("5. Tariq Road\n");
        printf("6. Tipu Sultan Road\n");
        printf("7. FAST NU (Destination)\n");
    } else {
        printf("Direct pickup and campus transit available for Route ID [%d].\n", id);
    }
    printf("----------------------------------------\n");
}

int main() {
    int choice;
    struct Student registeredStudent; 
    int hasRegistered = 0;            
    do {
        printf("\n========================================\n");
        printf("   FAST-TRANSIT: AUTOMATED SYSTEM     \n");
        printf("========================================\n");
        printf("1. View All Available Routes & Distances (46 Routes)\n");
        printf("2. Register Student & Calculate Fare\n");
        printf("3. Save Record & Generate Transport Pass\n");
        printf("4. View All Saved Student Records\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input! Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }
        switch(choice) {
            case 1: {
                FILE *f = fopen("routes.txt", "r");
                if (f == NULL) {
                    printf("\n[Error] Could not open routes data file!\n");
                    break;
                }
                printf("\n--- FAST-NUCES Transit Routes Network (Total: 46) ---\n");
                char line[256];
                while (fgets(line, sizeof(line), f) != NULL) {
                    int id;
                    char rName[60], bus[20];
                    float dist;    
                    sscanf(line, "%d,%59[^,],%f,%19s", &id, rName, &dist, bus);
                    printf("[%d] %s | Distance: %.1f km | Bus: %s\n", id, rName, dist, bus);
                }
                fclose(f);

                int checkId;
                printf("\nDo you want to view stops for a specific route?\n");
                printf("Enter Route ID (1-46, or enter 0 to return to menu): ");
                scanf("%d", &checkId);
                if (checkId >= 1 && checkId <= 46) {
                    printRouteStops(checkId);
                }
                break;
            }
            case 2: {
                printf("\n--- Student Registration & Fare Calculation ---\n");
                printf("Enter Full Name: ");
                scanf(" %[^\n]s", registeredStudent.name);
                printf("Enter Email Address: ");
                scanf(" %[^\n]s", registeredStudent.email);
                printf("Enter Contact Number: ");
                scanf(" %[^\n]s", registeredStudent.contact);
                printf("\nEnter Route ID (1-46): ");
                scanf("%d", &registeredStudent.routeChoice);

                FILE *f = fopen("routes.txt", "r");
                float selectedDist = 0;
                char selectedRouteName[60] = "";
                char selectedBus[20] = "";
                int found = 0;
                if (f != NULL) {
                    char line[256];
                    while (fgets(line, sizeof(line), f) != NULL) {
                        int id; char rName[60], bus[20]; float dist;
                        sscanf(line, "%d,%59[^,],%f,%19s", &id, rName, &dist, bus);
                        if (id == registeredStudent.routeChoice) {
                            selectedDist = dist;
                            strcpy(selectedRouteName, rName);
                            strcpy(selectedBus, bus);
                            found = 1;
                            break;
                        }
                    }
                    fclose(f);
                }
                if (!found || registeredStudent.routeChoice < 1 || registeredStudent.routeChoice > 46) {
                    printf("\n[Error] Invalid Route ID selected! Please choose between 1 and 46. Aborting.\n");
                    hasRegistered = 0;
                    break;
                }
                printf("\nSelect Membership Tier:\n");
                printf("1. Standard\n");
                printf("2. PRO (Includes Live ETA & Wi-Fi Access - Rs. 2000 Extra)\n");
                printf("Enter choice (1-2): ");
                scanf("%d", &registeredStudent.tier);

                printf("\nSelect Payment Mode:\n");
                printf("1. Monthly (Semester Total / 6)\n");
                printf("2. Semesterly (6-Month Upfront - 10%% Bulk Discount)\n");
                printf("Enter choice (1-2): ");
                scanf("%d", &registeredStudent.paymentMode);
                float semesterTotal = BASE_FEE + (selectedDist * RATE_PER_KM);
                if(registeredStudent.tier == 2) {
                    semesterTotal += 2000.0;
                }
                if(registeredStudent.paymentMode == 2) {
                    registeredStudent.finalFare = semesterTotal * 0.90; 
                    printf("\n[Notice] Semesterly Bulk Discount (10%%) Applied Successfully!\n");
                } else {
                    registeredStudent.finalFare = semesterTotal / SEMESTER_MONTHS; 
                }
                strcpy(registeredStudent.assignedBus, selectedBus);
                hasRegistered = 1;
                printf("\n========================================\n");
                printf("           FARE BREAKDOWN SUMMARY       \n");
                printf("========================================\n");
                printf("Student Name  : %s\n", registeredStudent.name);
                printf("Email         : %s\n", registeredStudent.email);
                printf("Contact       : %s\n", registeredStudent.contact);
                printf("Route         : %s\n", selectedRouteName);
                printf("Assigned Bus  : %s\n", selectedBus);
                printf("Distance      : %.1f km\n", selectedDist);
                printf("Membership    : %s\n", (registeredStudent.tier == 2) ? "PRO" : "Standard");
                printf("Payment Mode  : %s\n", (registeredStudent.paymentMode == 2) ? "Semesterly (Upfront)" : "Monthly Installment");
                if (registeredStudent.paymentMode == 2) {
                    printf("Final Semester Fare: Rs. %.2f\n", registeredStudent.finalFare);
                } else {
                    printf("Monthly Installment: Rs. %.2f / month\n", registeredStudent.finalFare);
                }
                break;
            }
            case 3: {
                printf("\n--- Save Record & Generate Transport Pass ---\n");
                if (!hasRegistered) {
                    printf("[Error] No student registered yet! Please complete Option 2 first.\n");
                    break;
                }
                FILE *f = fopen("routes.txt", "r");
                char rName[60] = ""; 
                int validRoute = 0;
                if (f != NULL) {
                    char line[256];
                    while (fgets(line, sizeof(line), f) != NULL) {
                        int id; char name[60], b[20]; float d;
                        sscanf(line, "%d,%59[^,],%f,%19s", &id, name, &d, b);
                        if (id == registeredStudent.routeChoice) {
                            strcpy(rName, name); 
                            validRoute = 1;
                            break;
                        }
                    }
                    fclose(f);
                }
                if (!validRoute) {
                    printf("[Error] Route information could not be verified.\n");
                    break;
                }
                FILE *file = fopen("transit_records.txt", "a");
                if (file == NULL) {
                    printf("[Error] Could not open file for writing!\n");
                    break;
                }
                char payMode[30];
                if (registeredStudent.paymentMode == 2) {
                    sprintf(payMode, "Semesterly: Rs. %.2f", registeredStudent.finalFare);
                } else {
                    sprintf(payMode, "Monthly: Rs. %.2f/mo", registeredStudent.finalFare);
                }
                fprintf(file, "Name: %s | Email: %s | Contact: %s | Route: %s | Bus: %s | %s\n",
                        registeredStudent.name, registeredStudent.email, registeredStudent.contact, rName, registeredStudent.assignedBus, payMode);
                fclose(file);
                printf("\n[Success] Student record for '%s' saved permanently to 'transit_records.txt'!\n", registeredStudent.name);
                break;
            }
            case 4: {
                FILE *file = fopen("transit_records.txt", "r");
                if (file == NULL) {
                    printf("\n[Info] No saved records found yet ('transit_records.txt' is empty).\n");
                    break;
                }
                printf("\n========================================\n");
                printf("       SAVED STUDENT PASS RECORDS       \n");
                printf("========================================\n");
                char buffer[256];
                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    printf("%s", buffer);
                }
                fclose(file);
                break;
            }
            case 5:
                printf("\nExiting FAST-Transit System. Good Bye!\n");
                break;
            default:
                printf("\n[Error] Invalid choice! Please select between 1 and 5.\n");
        }
    } while(choice != 5);
    return 0;
}

