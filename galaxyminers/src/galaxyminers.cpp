#include <galaxyminers.hpp>
#include "../utils/utils.cpp"
#include <eosio/crypto.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>

inline void verify_sha256_prefix(const std::string &value, const std::string &compared_hash)
{
  auto hash = eosio::sha256(value.c_str(), value.length());
  auto arr = hash.extract_as_byte_array();

  const char *hex_characters = "0123456789abcdef";
  std::string hash_prefix;
  const uint8_t *d = reinterpret_cast<const uint8_t *>(arr.data());

  auto prefix_size = compared_hash.length() / 2;
  for (uint32_t i = 0; i < prefix_size; ++i)
  {
    hash_prefix += hex_characters[d[i] >> 4];
    hash_prefix += hex_characters[d[i] & 0x0f];
  }

  eosio::check(compared_hash == hash_prefix,
               "fail to verify hash: " + compared_hash + " should be " + hash_prefix);
}

void nicegm::addplayer(eosio::name owner, eosio::name referral_partner)
{
  require_auth(owner);

  players user(_self, _self.value);

  // creates new user
  user.emplace(_self, [&](auto &u)
                    {
                      u.account = owner;
                      u.energy = 200;
                      u.max_energy = 1500;
                      u.last_mine_tx = (eosio::checksum256&)"0000000000000000000000000000000000000000000000000000000000000000";// eosio::sha256("0", 64);// 
                      u.balances =  std::vector<eosio::asset>();
                    });

  // Notify owner
  require_recipient(owner);
}

void nicegm::addconfitem(std::string schema_name, template_id_type template_id, std::string name, std::string img, bool can_burn) {
  configitem item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.schema_name = schema_name;
                        i.template_id = template_id;
                        i.name = name;
                        i.img = img;
                        i.can_burn = can_burn;
                      }
              );
}

void nicegm::delconfitem(template_id_type template_id) {
  // do something here to remove items
}

void nicegm::addsetting(energy_type init_energy, energy_type init_max_energy, uint32_t reward_noise_min, uint32_t reward_noise_max, std::uint8_t min_fee, std::uint8_t max_fee, std::uint64_t last_fee_updated, std::uint8_t fee) {
  setting con(_self, _self.value);

  con.emplace(_self, [&](auto &c)
                  {
                    c.init_energy = init_energy;
                    c.init_max_energy = init_max_energy;
                    c.reward_noise_min = reward_noise_min;
                    c.reward_noise_max = reward_noise_max;
                    c.min_fee = min_fee;
                    c.max_fee = max_fee;
                    c.last_fee_updated = last_fee_updated;
                    c.fee = fee;
                  }
  );
}

void nicegm::delsetting() {
  // do something here
}

void nicegm::addconfbadge(std::string name, std::uint32_t template_id, std::string type, std::string img, std::string badge_img, std::uint8_t saved_claims, std::uint8_t additional_slots, std::uint16_t additional_energy, std::uint8_t rewards_rate, std::uint8_t lucky, eosio::asset plasmas_mint, std::uint16_t coins_mint, std::uint64_t unstaking_time, std::uint64_t charged_time) {
  configbadge item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.name = name;
                        i.template_id = template_id;
                        i.type = type;
                        i.img = img;
                        i.badge_img = badge_img;
                        i.saved_claims = saved_claims;
                        i.additional_slots = additional_slots;
                        i.additional_energy = additional_energy;
                        i.rewards_rate = rewards_rate;
                        i.lucky = lucky;
                        i.plasmas_mint = plasmas_mint;
                        i.coins_mint = coins_mint;
                        i.unstaking_time = unstaking_time;
                        i.charged_time = charged_time;
                      }
              );
}

void nicegm::delconfbadge(std::uint32_t template_id) {
  // do something here to remove items
}

void nicegm::addbcraft(std:: uint32_t id, std::string name, std::string img, std::uint8_t saved_claims, std::uint8_t additional_slots, std::uint16_t additional_energy, std::uint8_t rewards_rate, std::uint8_t lucky, eosio::asset plasmas_mint, std::uint16_t coins_mint, std::uint64_t unstaking_time, std::uint64_t charged_time) {
  badgecraft item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.id = id;
                        i.name = name;
                        i.img = img;
                        i.saved_claims = saved_claims;
                        i.additional_slots = additional_slots;
                        i.additional_energy = additional_energy;
                        i.rewards_rate = rewards_rate;
                        i.lucky = lucky;
                        i.plasmas_mint = plasmas_mint;
                        i.coins_mint = coins_mint;
                        i.unstaking_time = unstaking_time;
                        i.charged_time = charged_time;
                      }
              );
}

void nicegm::tassetmint(eosio::name owner, std::string memo) {
  // do something here
}

void nicegm::addconftool(std::string template_name, std::string img,
eosio::name schema_name, eosio::name owner, std::string type, std::string rarity, std::uint8_t level, template_id_type template_id, energy_type energy_consumed, durability_type durability_consumed, std::vector<eosio::asset> mints, std::vector<eosio::asset> rewards, std::uint32_t charged_time) {
  require_auth(owner);

  configtools item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.template_id = template_id;
                        i.img = img;
                        i.schema_name = schema_name;
                        i.type = type;
                        i.rarity = rarity;
                        i.level = level;
                        i.template_id = template_id;
                        i.energy_consumed = energy_consumed;
                        i.durability_consumed = durability_consumed;
                        i.mints = mints;
                        i.rewards = rewards;
                        i.charged_time = charged_time;
                      }
              );
}

void nicegm::addgadget(asset_id_type asset_id, eosio::name owner, std::string type, template_id_type template_id, durability_type durability, durability_type current_durability, std::uint64_t next_availability)
{
  require_auth(owner);

  // Check if community was created before
  gadgets gadget(_self, _self.value);

  // creates new gadget
  gadget.emplace(_self, [&](auto &g)
                    {
                      g.asset_id = asset_id;
                      g.owner = owner;
                      g.type = type;
                      g.template_id = template_id;
                      g.durability = durability;
                      g.current_durability = current_durability;
                      g.next_availability = next_availability;
                    });

  // Notify owner
  require_recipient(owner);
}

void nicegm::claim(eosio::name asset_owner, asset_id_type asset_id, std::string img)
{
  require_auth(asset_owner);

  players player(_self, _self.value);
  gadgets gadget(_self, _self.value);
  configtools configtool(_self, _self.value);

  auto ct = configtool.find(string_to_uint64_t(img));
  auto iter = player.find(asset_owner.value);
  auto current_gadget = gadget.find(asset_id);
  
  eosio::check(ct != configtool.end(), "Not found configtool");
  eosio::check(iter != player.end(), "Not found player");
  eosio::check(current_gadget != gadget.end(), "Not found gadget");
  eosio::check(iter->energy - ct->energy_consumed > 0, "No enough energy");
  eosio::check(current_gadget->durability - ct->durability_consumed > 0, "No enough durability");

  
  gadget.modify(current_gadget, _self, [&](auto &g){
    g.durability = g.durability - ct->durability_consumed;
    auto nowWithSeconds = now() + ct->charged_time;
    g.next_availability = nowWithSeconds;
  });

  ///////////////////////////////////////////RESET//////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // // modify configtools data for this img
  // configtool.modify(ct, _self, [&](auto &g){
  //   g.charged_time = 60;
  // });
  // // delete all data in a table
  // auto it = gadget.begin();
  // while (it != gadget.end()) {
  //     it = gadget.erase(it);
  // }

  // // reset all data in players table
  // auto itp = player.begin();
  // while (itp != player.end()) {
  //     itp = player.erase(itp);
  // }
///////////////////////////////////////////////////END OF RESET//////////////////////////////////////////////////////////
  
  // Notify owner
  // require_recipient(asset_owner);

//////////////////////////////////////////////////////////FOR HELP//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // // using secondary index
  // // assume paymade_table is instantiated through contract constructor
  // auto pridx = paymade_table.get_index<N(loanid)>();
  // auto itr = pridx.find( SECONDARY_KEY_WHICH_YOU_WANT_TO_FIND );
  // pridx.modify(itr, same_payer, [&](auto& p) {
  //   /* updater */
  // });
}

void nicegm::testclaim(eosio::name asset_owner)
{
  require_auth(asset_owner);

  // players player(_self, _self.value);
  gadgets gadget(_self, _self.value);
  // configtools configtool(_self, _self.value);

  // delete all data in gadgets table
  auto it = gadget.begin();
  while (it != gadget.end()) {
      it = gadget.erase(it);
  }

  // auto ct = configtool.find(string_to_uint64_t("Qmc5wLioPQwhNh7GcP35gRs1upoLHeZNBur25hGSAUnvFh"));
}

void nicegm::addconfmkt(std::string schema_name, template_id_type template_id, std::string name, std::string img, std::vector<eosio::asset> cost) {
  configmarket con(_self, _self.value);

  con.emplace(_self, [&](auto &c)
                  {
                    c.schema_name = schema_name;
                    c.template_id = template_id;
                    c.name = name;
                    c.img = img;
                    c.cost = cost;
                  }
  );
}

void nicegm::delconfmkt(template_id_type template_id) {
  // do something here
}

EOSIO_DISPATCH(nicegm,
               (addplayer)(addconfitem)(delconfitem)(addsetting)(delsetting)(addconfbadge)(delconfbadge)(addbcraft)(tassetmint)(addgadget)(addconftool)(claim)(addconfmkt)(delconfmkt) // admin management
);
