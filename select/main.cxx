#include "../read/read.h"
#include <TFile.h>
#include <memory>

const std::string kTreeName   = "mctruth";
const std::string kFriendName = "";

bool select(const std::string &file, const std::string &exp, const std::string &outname)
{
    auto old_chain = open_root(file, kTreeName, kFriendName);
    TFile new_file(outname.c_str(), "recreate");
    auto new_chain = old_chain->CopyTree(exp.c_str());
    INFO("Writing: "+outname);
    new_file.Write();
    INFO("Writed.");
    return true;
}
void printUsage(const char* progName)
{
    std::cerr << "Usage: " << progName << " <selectFile> <selection> <outputFile>\n";
    std::cerr << "\n";
    std::cerr << "Options:\n";
    std::cerr << "  selectFile   Root file or list   (eg. select.list)\n";
    std::cerr << "  selection    Selection           (eg. chisq_kmfit<=100&&ratio_Kshort>=2)\n";
    std::cerr << "  outputFile   Output root file    (eg. selected.root)\n";
}
int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Error: invalid number of arguments (expected 3, got "
                  << (argc - 1) << ")\n";
        printUsage(argv[0]);
        return 1;
    }

    const char* selectFile = argv[1];
    const char* selection  = argv[2];
    const char* outputFile = argv[3];

    select(selectFile,
           selection,
           outputFile);
    // select("select.list",
    //         "1",
    //     "./selected.root");
    // select("../../inmc.list",
        // "chisq_kmfit<=100&&ratio_Kshort>=2&&m_Kshort>=0.47&&m_Kshort<=0.51",
    // "/scratchfs/bes/cloudsail/JpsiToPiKKshort/feat-PiPiandGamma/run/topo/selected.root");
    // select("../../data.list",
    //     "chisq_kmfit<=100&&ratio_Kshort>=2&&m_Kshort>=0.47&&m_Kshort<=0.51",
    // "/scratchfs/bes/cloudsail/JpsiToPiKKshort/feat-PiPiandGamma/run/data/selected.root");
    // select("../../exmc_pipi.list",
    //     "chisq_kmfit<=100&&ratio_Kshort>=2&&m_Kshort>=0.47&&m_Kshort<=0.51",
    // "/scratchfs/bes/cloudsail/JpsiToPiKKshort/feat-PiPiandGamma_only_PiPi/run/topo/selected.root");
    // select("../../exmc_pipigamma.list",
    //     "chisq_kmfit<=100&&ratio_Kshort>=2&&m_Kshort>=0.47&&m_Kshort<=0.51",
    // "/scratchfs/bes/cloudsail/JpsiToPiKKshort/feat-PiPiandGamma_only_PiPiGamma/run/topo/selected.root");
    return 0;
}
