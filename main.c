#include "box.h"
#include <stddef.h>
#include <stdio.h>

typedef struct {
  int x, y, z;
} Position;

typedef struct {
  char *friend_name;
  int friendship_level;
} Friend;

typedef struct {
  char *name;
  int age;
  float *scores;
  size_t num_scores;
  Position position;
  Friend *friends;
  size_t num_friends;
} Person;

int main() {
  int nooffriends = 3;
  int noofscores = 3;
  size_t length = 10;
  USING(char, pFriendsName,
        nooffriends *length) { // 3 friends 10 bytes of memory
    USING(Friend, pFriends, 3) {
      for (int i = 0; i < nooffriends; i++) {
        pFriends[i].friendship_level = i+1 * 10;
        pFriends[i].friend_name = &pFriendsName[i * length];
        snprintf(pFriends[i].friend_name, length, "Friend%d", i);
      }
      USING(float, pScores, noofscores) {
        for (int i = 0; i < noofscores; i++) {
          pScores[i] = i+1*10.00;
        }
        USING(char, pName, 10) {
          snprintf(pName, 10, "Loren");
          USING(Person, pPerson, 1) {
            pPerson->name = pName;
            pPerson->age = 22;
            pPerson->num_scores = noofscores;
            pPerson->scores = pScores;
            pPerson->position.x = 1;
            pPerson->position.y = 1;
            pPerson->position.z = 1;
            pPerson->num_friends = nooffriends;
            pPerson->friends = pFriends;
            printf("Person name : %s\n", pPerson->name);
            printf("Person age : %d\n", pPerson->age);
            printf("Person scores : %zu\n", pPerson->num_scores);
            for (int i = 0; i < pPerson->num_scores; i++) {
              printf("Score %d : %f\n", i, pPerson->scores[i]);
            }
            printf("Person position x : %d\n", pPerson->position.x);
            printf("Person position y : %d\n", pPerson->position.y);
            printf("Person position z : %d\n", pPerson->position.z);
            printf("Person friends : %zu\n", pPerson->num_friends);
            for (int i = 0; i < pPerson->num_friends; i++) {
              printf("Name : %s\n", pPerson->friends[i].friend_name);
              printf("Level : %d\n", pPerson->friends[i].friendship_level);
            }
          }
        }
      }
    }
  }
}
