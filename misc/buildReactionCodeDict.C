
std::string reactionCodesPath = "./reactionCodes.txt";

void buildReactionCodeDict(){

  std::vector<int> reactionCodesList;
  std::map<int, std::string> codesDict;
  std::map<int, int> colorsDict;


  auto lines = GenericToolbox::dumpFileAsVectorString(reactionCodesPath);
  for( auto& line : lines ){
    auto split = GenericToolbox::splitString(line, " : ");
    if( split.size() == 2 ){
      int code = std::stoi( GenericToolbox::trimString(split.at(0), " ") );
      codesDict[code] = GenericToolbox::trimString(split.at(1), " ");
      reactionCodesList.emplace_back(code);

      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "-->", "#rightarrow");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "ETA0", "#Eta_{0}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "LAMBDA", "#Lambda");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "GAMMA", "#gamma");

      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "NEUBAR", "#bar{#nu}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "NEU", "#nu");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "PI0", "#pi^{0}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "PI+", "#pi^{+}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "PI-", "#pi^{-}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "K0", "K^{0}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "K+", "K^{+}");
      GenericToolbox::replaceSubstringInsideInputString(codesDict[code], "K-", "K^{-}");

    }
  }

  std::cout << GenericToolbox::parseMapAsString(codesDict) << std::endl;

  int colorIndex{0};
  std::stringstream ss;
  ss << "# ReactionCode Dictionary" << std::endl;
  ss << "- { value: 0, title: \"UNDEFINED\", color: 1 } # kBlack" << std::endl;
  for( auto& reactionCode : reactionCodesList ){
    ss << "- { value: " << reactionCode
    << ", title: \"" << codesDict[reactionCode] << "\""
    << ", color: " << GenericToolbox::defaultColorWheel[colorIndex++ % GenericToolbox::defaultColorWheel.size()]
    << " }" << std::endl;
  }

  std::cout << ss.str() << std::endl;
  GenericToolbox::dumpStringInFile("ReactionCodesDict.yaml", ss.str());

}