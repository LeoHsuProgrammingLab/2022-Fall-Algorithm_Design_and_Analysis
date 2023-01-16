#include "splender.h"
#include<bits/stdc++.h>

using namespace std;

//record the board state
vector<card> stk_all_cards;
vector< vector<card> > stk_arr;
int stk_num[3] = {40, 30, 20};

int player_score[2] = {0, 0}, gem_state[6] = {4, 4, 4, 4, 4, 4}, player_gem_state[2][7], in_hand[2][5], buffer_cnt[3];

set<int> imprisoned_table[2], buffer_table[3];

int gem_pos_arr[10][3] = {
  {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 3}, {0, 2, 4}, {0, 3, 4}, {1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}
};

void check_buffer_table (vector< vector<card> > v) {
  for (int i = 0; i < 3; i++) {
    while (buffer_table[i].size() < 4 && buffer_cnt[i] < stk_num[i]) {
      buffer_table[i].insert(v[i][buffer_cnt[i]].id);
      buffer_cnt[i]++;
    }
  }
}

bool cmp_id (const card &x, const card &y) {
  return x.id < y.id;
}

void init (vector<card> stack_1, vector<card> stack_2, vector<card> stack_3) {
  
  //store whole cards
  stk_all_cards.resize(0);
  for (int i = 0; i < 40; i++) {
    stk_all_cards.push_back(stack_1[i]);
  }
  for (int i = 0; i < 30; i++) {
    stk_all_cards.push_back(stack_2[i]);
  }
  for (int i = 0; i < 20; i++) {
    stk_all_cards.push_back(stack_3[i]);
  }

  sort(stk_all_cards.begin(), stk_all_cards.end(), cmp_id);

  //store individual array cards
  stk_arr.push_back(stack_1);
  stk_arr.push_back(stack_2);
  stk_arr.push_back(stack_3);
  
  //insert card id to the buffer
  for(int i = 0; i<3; i++){
    buffer_cnt[i] = 0;
  }
  check_buffer_table(stk_arr);
}

int find_stack_num (int id) {
  if (id < stk_num[0]) {
    return 0;
  }
  if (id < stk_num[0] + stk_num[1]) {
    return 1;
  }
  if (id < stk_num[0] + stk_num[1] + stk_num[2]) {
    return 2;
  }
  exit(-1);
}

bool is_illegal (struct move m, int player) {
  int sum = 0, mx = INT_MIN, mn = INT_MAX, tmp = 0;
  bool flag = true;
  switch (m.type) {
    case 1:
      // check the combination is legal
      for (int i = 0; i < 5; i++) {
        sum +=  m.gem[i];
        mx = max(mx, m.gem[i]);
        mn = min(mn, m.gem[i]);
      }
      switch (sum) {
        case 2:
          if (mx != 2 || mn != 0) {
            return true;
          }
          break;
        case 3:
          if (mx != 1 || mn != 0) {
            return true;
          }
          break;
        default:
          return true;
      }
      // check the remain gem in pubilic is enough
      for (int i = 0; i < 5; i++) {
        if (m.gem[i] > gem_state[i]) {
          return true;
        }
      }
      // check over limit of hand
      return player_gem_state[player][6] + sum > 10;
    case 2:
      // check the card is on the board or imprisoned
      if ((!buffer_table[find_stack_num(m.card_id)].count(m.card_id)) && (!imprisoned_table[player].count(m.card_id))) {
        return true;
      }
      // check the player has enough gem
      for (int i = 0; i < 5; i++) {
        if (player_gem_state[player][i] + in_hand[player][i] < stk_all_cards[m.card_id].cost[i]) {
          tmp += stk_all_cards[m.card_id].cost[i] - player_gem_state[player][i] - in_hand[player][i];
          
        }
      }
      return tmp > player_gem_state[player][5];
    case 3:
      // check the card is on the board
      if (!buffer_table[find_stack_num(m.card_id)].count(m.card_id)) {
        return true;
      }
      // check whether take the gem lead to over 10
      if (player_gem_state[player][6] >= 10 || gem_state[5] <= 0) {
        return true;
      }
      // check over the limit of the imprison card
      return imprisoned_table[player].size() >= 3;
    default:
      return true;
  }
}

bool play_a_move (struct move m, int player) {
  switch (m.type) {
    case 1:
      // get the gem from the public area
      for (int i = 0; i < 5; i++) {
        gem_state[i] -= m.gem[i];
        player_gem_state[player][i] += m.gem[i];
        player_gem_state[player][6] += m.gem[i];
      }
      break;
    case 2:
      // put the gem into the public area
      for (int i = 0; i < 5; i++) {
        int tmp_gem = max(stk_all_cards[m.card_id].cost[i] - in_hand[player][i], 0);
        if (tmp_gem > player_gem_state[player][i]) {
          player_gem_state[player][5] -= tmp_gem - player_gem_state[player][i];
          player_gem_state[player][6] -= tmp_gem - player_gem_state[player][i];
          gem_state[5] += tmp_gem - player_gem_state[player][i];
          tmp_gem = player_gem_state[player][i];
        }
        player_gem_state[player][i] -= tmp_gem;
        player_gem_state[player][6] -= tmp_gem;
        gem_state[i] += tmp_gem;
      }
      // get the card from the board or imprisoned
      if (buffer_table[find_stack_num(m.card_id)].count(m.card_id)) {
        buffer_table[find_stack_num(m.card_id)].erase(m.card_id);
      }
      else {
        imprisoned_table[player].erase(m.card_id);
      }
      in_hand[player][stk_all_cards[m.card_id].gem]++;
      player_score[player] += stk_all_cards[m.card_id].score;
      break;
    case 3:
      // imprison the card
      buffer_table[find_stack_num(m.card_id)].erase(m.card_id);
      imprisoned_table[player].insert(m.card_id);
      // get special gem
      gem_state[5]--;
      player_gem_state[player][5]++;
      player_gem_state[player][6]++;
      break;
  }
  return player_score[player] >= 15;
}


//cards moves
struct move buy_or_rsv(struct card c, int type){
  struct move m;
  m.type = type;
  m.card_id = c.id;

  return m;
}

float value_function(struct move m){
  float score = 0, wl = 0, bonus = 0, gems = 0, dst = 0; 

  switch (m.type){
    case 1:
      for(int i = 0; i<5; ++i){
        gems += m.gem[i];
      }
      if(!imprisoned_table[0].empty()){
        for(auto itr : imprisoned_table[0]){
          for(int i = 0; i<5; ++i){
            if(m.gem[i] != 0 && stk_all_cards[itr].cost[i] != 0 && stk_all_cards[itr].cost[i] < 5){
              dst += m.gem[i] + player_gem_state[0][i] + in_hand[0][i] - stk_all_cards[itr].cost[i];
            }
          }
        }
      }else{
        for(int i = 0; i<3; ++i){
          for(int j = 0; j<4; ++j){
            for(int k =0; k<5; ++k){
              if(m.gem[k] != 0 && stk_arr[i][j].cost[k] != 0 && stk_arr[i][j].cost[k] < 5){
                dst += 0.5;
              }
            }
          }
        }
      }
      break;
    case 2:
      score = stk_all_cards[m.card_id].score;
      bonus = stk_all_cards[m.card_id].gem;
      if(player_score[0] + score >= 15){
        wl = 1;
      }
      break;
    case 3:
      gems = 2;
      for(int i = 0; i<5; ++i){
        if(stk_all_cards[m.card_id].cost[i] > 4) dst += -10000;
        else if(stk_all_cards[m.card_id].cost[i] == 4) dst -= 0.5;
        dst += player_gem_state[0][i] + in_hand[0][i] - stk_all_cards[m.card_id].cost[i];//will be negative
      }
      break;
  }

  float result = 100*wl + 5*score + 1.5*bonus + 0.5*gems + dst;
  // cout << 5*score << " " << 1.5*bonus << " " << 0.5 * gems << " " << 0.1*dst << " result = " << result << "\n";
  return result;
}

struct move player_move (struct move server_m) {
  play_a_move(server_m, 1);
  check_buffer_table(stk_arr);

  vector<struct move> move_queue;

  //make m as various type
  struct move m;
  //Buy & RSV
  for(int i = 0; i<3; ++i){
    for(int j = 0; j<4; ++j){
      struct card c = stk_arr[i][j];
      move_queue.push_back(buy_or_rsv(c, 2));
      move_queue.push_back(buy_or_rsv(c, 3));
    }
  }
  //Get Gems
  //2
  struct move temp; temp.type = 1;
  for(int i = 0; i<5; ++i){
    temp.gem[i] = 0;
  }
  for(int i = 0; i<5; ++i){
    temp.gem[i] = 2;
    move_queue.push_back(temp);
    temp.gem[i] = 0;
  }
  //3
  for(int i = 0; i<10; ++i){
    for(int j = 0; j<3; ++j){
      temp.gem[ gem_pos_arr[i][j] ] = 1;
    }
    move_queue.push_back(temp);
    for(int j = 0; j<3; ++j){
      temp.gem[ gem_pos_arr[i][j] ] = 0;
    }
  }

  //check if legal
  int size = move_queue.size();
  float value = INT_MIN; float temp_val = 0;
  
  for(int i = 0; i<size; ++i){
    if(!is_illegal(move_queue[i], 0)){
      // cout << "queue i : " << i << "\n";
      temp_val = value_function(move_queue[i]);
      if(value < temp_val){
        value = temp_val; m = move_queue[i];
      }
    }
  }
  play_a_move(m, 0);

  return m;
}
