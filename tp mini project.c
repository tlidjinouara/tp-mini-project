#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int number;
    char name[50];
    char password[50];
    float balance;
} Account;
.accumulate
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached!\n");
        return;
    }

    Account acc;
    printf("Enter account number: ");
    scanf("%d", &acc.number);
    printf("Enter your name: ");
    scanf("%s", acc.name);
    printf("Enter password: ");
    scanf("%s", acc.password);
    acc.balance = 0.0;

    accounts[accountCount] = acc;
    accountCount++;

    printf("Account created successfully!\n");
}

int findAccount(int number, char password[]) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == number && strcmp(accounts[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void depositMoney(int index) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    accounts[index].balance += amount;
    printf("Deposit successful!\n");
}

void transferMoney(int index) {
    int targetNumber;
    float amount;
    printf("Enter target account number: ");
    scanf("%d", &targetNumber);
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if (accounts[index].balance < amount) {
        printf("Not enough balance!\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].number == targetNumber) {
            accounts[index].balance -= amount;
            accounts[i].balance += amount;
            printf("Transfer successful!\n");
            return;
        }
    }

    printf("Target account not found.\n");
}

void checkBalance(int index) {
    printf("Your balance is: %.2f DA\n", accounts[index].balance);
}

void deleteAccount(int index) {
    if (accounts[index].balance != 0) {
        printf("You can only delete an account if the balance is 0.\n");
        return;
    }

    for (int i = index; i < accountCount - 1; i++) {
        accounts[i] = accounts[i + 1];
    }

    accountCount--;
    printf("Account deleted successfully.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Welcome to the Bank System ---\n");
        printf("1. Create a New Account\n");
        printf("2. Log In to Account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createAccount();
        } else if (choice == 2) {
            int number;
            char password[50];
            printf("Enter account number: ");
            scanf("%d", &number);
            printf("Enter password: ");
            scanf("%s", password);

            int index = findAccount(number, password);
            if (index == -1) {
                printf("Incorrect account number or password.\n");
            } else {
                int action;
                do {
                    printf("\n1. Deposit Money\n");
                    printf("2. Transfer Money\n");
                    printf("3. Check Balance\n");
                    printf("4. Delete Account\n");
                    printf("5. Log Out\n");
                    printf("Enter your choice: ");
                    scanf("%d", &action);

                    if (action == 1) depositMoney(index);
                    else if (action == 2) transferMoney(index);
                    else if (action == 3) checkBalance(index);
                    else if (action == 4) {
                        deleteAccount(index);
                        action = 5;
                    }
                    else if (action != 5) printf("Invalid choice!\n");

                } while (action != 5);
            }
        } else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
