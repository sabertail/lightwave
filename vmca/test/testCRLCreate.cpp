#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <pkcs_types.h>
#include <pkcs_botan.h>
#include <pkcs_csr.h>

using namespace std;

int main(int argc, char **argv)
{
	std::string rootDir("/home/anue/vmca-final/vmca/obj/test/");
	std:string delCmd("rm -rf ");
	delCmd.append(rootDir);
	delCmd.append("*.pem");

	std::string CertName("testCSA");
	system(delCmd.c_str());
	VMCAAllocatePrivateKeyP((char*)rootDir.c_str(),(char*)CertName.c_str(),"",1024);

	PVMCA_PKCS_10_REQ_DATA pCertRequestData = NULL;
	VMCAAllocatePKCS10Data(&pCertRequestData);

	VMCAInitPKCS10Data(
        "Anue",
        "Anu Engineer",
        "vmware Engineering",
        "WA",
        "US",
        "aengineer@vmware.com",
        "127.0.0.1",
        pCertRequestData);

	std::string Priv_Key(rootDir);
	Priv_Key.append("/");
	Priv_Key.append(CertName);
	Priv_Key.append(".priv.pem");

	char* pAllocatedCSR = NULL;

	VMCACreateSigningRequestP(
    pCertRequestData,
    (char*) Priv_Key.c_str(),
    "",
    &pAllocatedCSR);

  	ofstream csrFile;
  	csrFile.open ("TestCSA.csr");
 	csrFile << pAllocatedCSR;
 	csrFile.close();
 	system("openssl req -in TestCSA.csr -noout -text > decoded.txt");
  
}  
