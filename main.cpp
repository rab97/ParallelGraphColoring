//
// Created by rab97 on 29/12/21.
//

#include "classes/Graph.h"

#include "parse/Parser.h"
#include "resolve/Resolve.h"

int main(int argc, char **argv) {
    std::vector <std::string> args(argv, argv + argc);
    if (args.size() < 2) {
        std::cerr << "Usage" << std::endl << std::endl << " " << args[0] << " [--run-all] " << "<path_graph_to_run>"
                  << std::endl << " " << args[0] << " [--run-single] " << "<path_graph_to_run" << " [options]"
                  << std::endl << std::endl << "Run '" << args[0] << " --help' for more informations." << std::endl
                  << std::endl;
        return -1;
    }

    bool help = std::find(args.begin(), args.end(), "--help") != args.end();
    bool run_all = std::find(args.begin(), args.end(), "--run-all") != args.end();
    bool run_single = std::find(args.begin(), args.end(), "--run-single") != args.end();

    if (help) {
        std::cout << "Usage" << std::endl << std::endl << " " << args[0] << " [--run-all] " << "<path_graph_to_run>"
                  << std::endl << " " << args[0] << " [--run-single] " << "<path_graph_to_run" << " [options]"
                  << std::endl << std::endl << "Options" << std::endl << " sequential\t"
                  << "= Execute sequential algorithm\n"
                  << " ldf\t\t" << "= Execute Largest Degree First algorithm\n" << " sdl\t\t"
                  << "= Execute Smallest Degree Last algorithm\n"
                  << " mis\t\t" << "= Execute Maximal Indipendent Set algorithm\n"
                  << " luby\t\t" << "= Execute Luby algorithm\n"
                  << " jp\t\t" << "= Execute Jones-Plassmann algorithm\n";
    } else if (run_all) {
        if (args.size() < 3) {
            std::cerr << "Error: <graph_to_run> not specified" << std::endl <<
                      "Error: Run '" << args[0] << " --help' for more informations." << std::endl;
            return -1;
        }
        Parser p(args.back());
        Graph graph = p.parse();
        Resolve resolve(graph);
        resolve.resolve_all(args.back());
    } else if (run_single) {
        if (args.size() < 3) {
            std::cerr << "Error: <graph_to_run> not specified" << std::endl <<
                      "Error: Run '" << args[0] << " --help' for more informations." << std::endl;
            return -1;
        }
        if (args.size() < 4) {
            std::cerr << "Error: <option> not specified" << std::endl <<
                      "Error: Run '" << args[0] << " --help' for more informations." << std::endl;
            return -1;
        }
        std::string arg = args.back();
        if (arg != "sequential" && arg != "ldf" && arg != "sdl" && arg != "mis" && arg != "luby" && arg != "jp") {
            std::cerr << "Error: Unknown option " << args.back() << std::endl <<
                      "Error: Run '" << args[0] << " --help' for all supported options." << std::endl;
            return -1;
        }
        Parser p(args[2]);
        Graph graph = p.parse();
        Resolve resolve(graph, args.back());
        resolve.resolve_all(args[2]);
    } else {
        std::cerr << "Error: Unknown argument " << args.back() << std::endl <<
                  "Error: Run '" << args[0] << " --help' for more informations." << std::endl;
        return -1;
    }

    return 0;
}
