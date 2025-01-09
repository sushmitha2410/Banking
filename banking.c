#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10
#define MAX_NAME_LEN 50

typedef struct
{
  int accountNumber;
  char name[MAX_NAME_LEN];
  float balance;
  char transactionHistory[100][200];
  int transactionCount;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void createAccount()
{
  if (accountCount >= MAX_ACCOUNTS)
  {
    printf("Account limit reached. Cannot create more accounts.\n");
    return;
  }

  Account newAccount;
  printf("Enter account number: ");
  scanf("%d", &newAccount.accountNumber);
  getchar(); // To consume newline character
  printf("Enter name: ");
  fgets(newAccount.name, MAX_NAME_LEN, stdin);
  newAccount.name[strcspn(newAccount.name, "\n")] = 0; // Remove newline character
  newAccount.balance = 0.0;
  newAccount.transactionCount = 0;

  accounts[accountCount] = newAccount;
  accountCount++;
  printf("Account created successfully!\n");
}

void deleteAccount()
{
  int accountNumber;
  printf("Enter account number to delete: ");
  scanf("%d", &accountNumber);

  for (int i = 0; i < accountCount; i++)
  {
    if (accounts[i].accountNumber == accountNumber)
    {
      for (int j = i; j < accountCount - 1; j++)
      {
        accounts[j] = accounts[j + 1];
      }
      accountCount--;
      printf("Account deleted successfully!\n");
      return;
    }
  }
  printf("Account not found.\n");
}

void deposit()
{
  int accountNumber;
  float amount;
  printf("Enter account number: ");
  scanf("%d", &accountNumber);
  printf("Enter deposit amount: ");
  scanf("%f", &amount);

  for (int i = 0; i < accountCount; i++)
  {
    if (accounts[i].accountNumber == accountNumber)
    {
      accounts[i].balance += amount;
      snprintf(accounts[i].transactionHistory[accounts[i].transactionCount], sizeof(accounts[i].transactionHistory[accounts[i].transactionCount]), "Deposited: %.2f", amount);
      accounts[i].transactionCount++;
      printf("Deposit successful! New balance: %.2f\n", accounts[i].balance);
      return;
    }
  }
  printf("Account not found.\n");
}

void withdraw()
{
  int accountNumber;
  float amount;
  printf("Enter account number: ");
  scanf("%d", &accountNumber);
  printf("Enter withdrawal amount: ");
  scanf("%f", &amount);

  for (int i = 0; i < accountCount; i++)
  {
    if (accounts[i].accountNumber == accountNumber)
    {
      if (accounts[i].balance >= amount)
      {
        accounts[i].balance -= amount;
        snprintf(accounts[i].transactionHistory[accounts[i].transactionCount], sizeof(accounts[i].transactionHistory[accounts[i].transactionCount]), "Withdrawn: %.2f", amount);
        accounts[i].transactionCount++;
        printf("Withdrawal successful! New balance: %.2f\n", accounts[i].balance);
      }
      else
      {
        printf("Insufficient funds.\n");
      }
      return;
    }
  }
  printf("Account not found.\n");
}

void viewTransactions()
{
  int accountNumber;
  printf("Enter account number: ");
  scanf("%d", &accountNumber);

  for (int i = 0; i < accountCount; i++)
  {
    if (accounts[i].accountNumber == accountNumber)
    {
      printf("Transaction history for account %d:\n", accountNumber);
      for (int j = 0; j < accounts[i].transactionCount; j++)
      {
        printf("%s\n", accounts[i].transactionHistory[j]);
      }
      return;
    }
  }
  printf("Account not found.\n");
}

void updateDetails()
{
  int accountNumber;
  printf("Enter account number: ");
  scanf("%d", &accountNumber);

  for (int i = 0; i < accountCount; i++)
  {
    if (accounts[i].accountNumber == accountNumber)
    {
      printf("Updating details for account %d\n", accountNumber);
      getchar(); // To consume newline character
      printf("Enter new name: ");
      fgets(accounts[i].name, MAX_NAME_LEN, stdin);
      accounts[i].name[strcspn(accounts[i].name, "\n")] = 0; // Remove newline character
      printf("Account details updated successfully!\n");
      return;
    }
  }
  printf("Account not found.\n");
}

int main()
{
  int choice;
  do
  {
    printf("\nBanking Management System\n");
    printf("1. Create Account\n");
    printf("2. Delete Account\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. View Transactions\n");
    printf("6. Update Account Details\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      createAccount();
      break;
    case 2:
      deleteAccount();
      break;
    case 3:
      deposit();
      break;
    case 4:
      withdraw();
      break;
    case 5:
      viewTransactions();
      break;
    case 6:
      updateDetails();
      break;
    case 7:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 7);

  return 0;
}
