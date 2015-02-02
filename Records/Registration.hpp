
#ifndef REGISTRATION
#define REGISTRATION

#include "Record.hpp"
#include <vector>
#include <string>
#include <ostream>

typedef std::pair<uint8_t*, size_t> UInt32Data;

class Registration: public Record
{
    public:
        static const int DIFFICULTY = 4; //1/2^x chance of success, so order of magnitude
        static const uint32_t THRESHOLD = UINT32_MAX / (1 << DIFFICULTY);

        Registration(const std::string&, uint8_t[SHA256_LEN],
            const std::string&, Botan::RSA_PrivateKey*);
        ~Registration();

        bool setName(const std::string&);
        bool addSubdomain(const std::string&, const std::string&);
        bool setContact(const std::string&);
        bool setKey(Botan::RSA_PrivateKey*);
        bool refresh();
        bool makeValid(uint8_t);
        bool isValid() const;
        std::string getOnion() const;
        UInt32Data getPublicKey() const;
        std::string asJSON() const;
        friend std::ostream& operator<<(std::ostream&, const Registration&);

        enum WorkStatus
        {
            Success, NotFound, Aborted
        };

    private:
        UInt32Data getCentral(uint8_t* nonce) const;
        WorkStatus mineParallel(uint8_t);
        WorkStatus makeValid(uint8_t, uint8_t, uint8_t*, uint8_t*, uint8_t*);

        std::string name_;
        std::vector<std::pair<std::string,std::string>> subdomains_;
        std::string contact_;
        long timestamp_;
        uint8_t consensusHash_[SHA256_LEN];
        uint8_t nonce_[NONCE_LEN];
        uint8_t scrypted_[SCRYPTED_LEN];
        uint8_t signature_[SIGNATURE_LEN];
        Botan::RSA_PrivateKey* key_;
        bool valid_;
};

#endif