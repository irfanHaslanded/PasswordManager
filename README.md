# PasswordManager
A secure password manager, that can create very strong passwords for you, for a large number of websites, and a large number of users

# Details
When you really need to keep your passwords safe.
All application data is stored in a file passwdMgr.\<userName\>.dat

1. There are 2 secrets derived from your master password
   a. The first secret is used for logging you into the program
   b. The second secret is used for generating new passwords for every username@site.com
2. All secrets are strong and one-way, and not stored anywhere
3. Two salts are stored for each secret
4. Only the hash of the first secret is stored
5. Only the user-accounts data is stored


# Usage:
passwd-mgr
  # commands
  ```
  login
  create-password username@site
  show-passwprd username@site
  show-accounts
  logout
  exit
  ```
# Example
```
C:\Users\snowWhite> passwd-mgr
passMgr> login
Enter username: SnowWhite
Enter Master Password: 
Confirm master password:
Successfully generated a master password.
SnowWhite@passMgr> create-password snowgirl@google.com
Password is: x&:@6R?!Q{wFm_.)
SnowWhite@passMgr> show-password snowgirl@google.com
Password is: x&:@6R?!Q{wFm_.)
SnowWhite@passMgr> create-password snowIsWhite@twitter.com
Password is: W\kry{Z88<98E2dr
SnowWhite@passMgr> create-password snowIsWhite@twitter.com
Password is: VBP9p;Tw2s;gZ);_
SnowWhite@passMgr> show-accounts
snowgirl@google.com
snowIsWhite@twitter.com
SnowWhite@passMgr> logout
passMgr> exit
```
