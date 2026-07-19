int loginSystem(char *account) {
    FILE *fp;
    char account_stored[100], password_stored[100], user_account[100], user_password[100];
    char *account_list, *password_list;
    int i, j, number = 10, count = 0;
    
    // dynamic memory allocation
    account_list = malloc(number * 100);
    password_list = malloc(number * 100);
    
    // read the account file
    fp = fopen("account.txt", "r");
    if (fp == NULL) {
        printf("Cannot open the file!\n");
        free(account_list);
        free(password_list);
        return 0;
    }
    
    while(fscanf(fp, "%99s%99s", account_stored, password_stored) == 2) {
        if (count >= number) { // allocate more memory if not enough
            account_list = realloc(account_list, 2 * number * 100);  
            password_list = realloc(password_list, 2 * number * 100);
            number = 2 * number;
        }
        strcpy(account_list + count * 100, account_stored);
        strcpy(password_list + count * 100, password_stored);
        count++;
     
    }
    
    // test if the account file is empty
        if (count == 0) {
            printf("No data found!\n");
            fclose(fp);
            free(account_list);
            free(password_list);
            return 0;
        }
    
    for (i = 0; i <= 2; i++) {
        j = 0;
        
        // input account and password by users 
        printf("Please input your account: ");
        scanf("%99s", user_account);
        printf("Please input your password: ");
        scanf("%99s", user_password);
        
        // test the account
        while (strcmp(user_account, account_list + j * 100) != 0) {
            j++;
            if (j == count) {
                printf("Invalid account name or password!\n");
                break;
            }
        }
        if (j == count)
            continue;
            
        // test the password
        if (strcmp(user_password, password_list + j * 100) == 0) {
            printf("Login Successful!\n");
            fclose(fp);
            free(account_list);
            free(password_list);
            strcpy(account, user_account);
            return 1;
        }
        else {
            printf("Invalid account name or password!\n");
            continue;    
        }
    } 
    
    // exit the login system
    printf("You have failed three times!\n");
    fclose(fp);
    free(account_list);
    free(password_list);
    return 0;
}