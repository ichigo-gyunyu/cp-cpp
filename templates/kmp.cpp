#include <string>
#include <vector>
class KMP {
  public:
    explicit KMP(const std::string& needle) : needle_(needle) {}

    explicit KMP(const std::string&& needle) : needle_(needle) {}

    std::vector<int> GetLPS() {
        if (!builtLps_)
            BuildLPS_();
        return lps_;
    }

    int Search(const std::string& haystack) {
        if (!builtLps_)
            BuildLPS_();

        size_t n = haystack.size(), m = needle_.size();
        if (m == 0) {
            return 0;
        }

        for (size_t i = 0, j = lps_[0]; i < n;) {
            if (haystack[i] == needle_[j])
                i++, j++;

            if (j == m)
                return i - j;

            if (i == n)
                return -1;

            if (haystack[i] != needle_[j]) {
                if (j != 0)
                    j = lps_[j - 1];
                else
                    i++;
            }
        }

        return -1;
    }

  private:
    std::string needle_;
    bool builtLps_ = false;
    std::vector<int> lps_;

    void BuildLPS_() {
        size_t m = needle_.size();
        lps_.assign(m, 0);
        for (size_t i = 1; i < m; i++) {
            int prevLPS = lps_[i - 1];
            while (prevLPS > 0 && needle_[i] != needle_[prevLPS])
                prevLPS = lps_[prevLPS - 1];
            if (needle_[i] == needle_[prevLPS])
                prevLPS++;
            lps_[i] = prevLPS;
        }
        builtLps_ = true;
    }
};
