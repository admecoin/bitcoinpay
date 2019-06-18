#ifndef obfuscationCONFIG_H
#define obfuscationCONFIG_H

#include <QDialog>

namespace Ui
{
class obfuscationConfig;
}
class WalletModel;

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class obfuscationConfig : public QDialog
{
    Q_OBJECT

public:
    obfuscationConfig(QWidget* parent = 0);
    ~obfuscationConfig();

    void setModel(WalletModel* model);


private:
    Ui::obfuscationConfig* ui;
    WalletModel* model;
    void configure(bool enabled, int coins, int rounds);

private slots:

    void clickBasic();
    void clickHigh();
    void clickMax();
};

#endif // obfuscationCONFIG_H
