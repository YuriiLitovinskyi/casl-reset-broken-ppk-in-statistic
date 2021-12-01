#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Current program will reset all broken lines(zones), which leads to removing device from Broken in Statistics


int main(int argc, char *argv[]) {
	
    sqlite3 *db;
    char *err_msg = 0;
  
    
    // Open CASL DB
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open CASL Cloud database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    }
    
    
    // query to change status of the line from Broken to Norm
    char deleteBrokenStatus[256] = "UPDATE device_line SET is_broken = 0 WHERE is_broken = 1";
    
    rc = sqlite3_exec(db, deleteBrokenStatus, 0, 0, &err_msg);   
        
     
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
    
    sqlite3_close(db);  
    
    printf("\nDevices status was reset successfully! \n");
    
    system("pause");   
       
	return 0;
}
