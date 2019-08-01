# Logic

### Master Password 
0. Add a pepper to the master password. Pepper is derived from username, and master password and some mixing
```C
char *master_password = mix_password(username, password);
```

1. A 32 byte random salt is used. a sha 1024 hash is used to store the master password. This is the only hash that is stored.
   The only use for the master_hash is to authenticate you as the user.
```C 
char *master_hash = encrypt_password(master_salt, master_password);
```
2. A 32 byte random salt is used for creating secrets for user accounts.
```C
char *app_hash = encrypt_password(app_salt, master_password);
```
3. Use the app_hash to derive passwords for each account
```C
char *account_password = create_password(app_hash, user_account);
```
a new salt is created for this user_account and a new password is computed.

4. Retrieve the password for a specified account
```C
char *account_password = get_password(app_hash, user_account);
```
compute the password for the user_account and stored account_salt.

### Data Structures
```C
typedef struct {
  char account_name[128]; // account_name of the format username@account.com
  char account_salt[16];  // salt used for creating the password of this account.
} AccountData;

typedef struct {
  char username[64];              // username for the passwd-mgr account
  char master_salt[32];           // salt used for master_hash
  char master_hash[1024];         // hash to use for logging in the user into passwd-mgr
  char app_salt[32];              // salt to use for app password creation using master password
  AccountData account_data[1024]; // max of 1024 accounts per user
} UserData;
```
