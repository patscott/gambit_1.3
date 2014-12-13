//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Scanner method implementations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 May, June, July
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 July 2013/Feb 2014
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Aug
///
///  *********************************************

#ifndef __scan_hpp__
#define __scan_hpp__

#include "yaml_parser.hpp"
#include "priors.hpp"
#include "printer_interface.hpp"
#include "plugin_interface.hpp"
#include "priors/composite.hpp"

namespace Gambit
{
        namespace Scanner
        {       
                class Factory_Base
                {
                public:
                        virtual const std::vector<std::string> & getKeys() const = 0;
                        virtual unsigned int getDim() const = 0;
                        virtual void * operator() (const std::string &in, const std::string &purpose) const = 0;
                        virtual void remove(void *a) const = 0;
                        virtual ~Factory_Base() {};
                };
                
                class Function_Base
                {
                public:
                        virtual double operator () (const std::vector<double> &) = 0;
                        virtual void print(double, const std::string &) const = 0;
                        virtual ~Function_Base(){} 
                };

                class IniFileInterface_Base
                {
                public:
                        virtual const std::string pluginName() const = 0;
                        virtual const std::string fileName() const = 0;
                        virtual const std::string getValue(const std::string &in) const = 0;
                        virtual YAML::Node getNode(const std::string &str) const = 0;
                        virtual ~IniFileInterface_Base() {};
                };
                
                struct iniPluginStruct
                {
                        std::string plugin;
                        std::string version;
                        std::string library;
                        
                        iniPluginStruct() : plugin(""), version(""), library("") {}
                };
                
                class Gambit_Scanner
                {
                private:
                        const Factory_Base *factory;
                        const Priors::CompositePrior *prior;
                        printer_interface *printerInterface;
                        Options options;
                        Plugin::Plugin_Loader plugins;
                        std::map<std::string, iniPluginStruct> iniPlugs;

                public:
                        Gambit_Scanner (const Factory_Base &factory, const Options &options, const Priors::CompositePrior &prior, printer_interface *printerInterface = 0);

                        int Run();
                        
                        std::vector<Plugin::PluginStruct> getPluginsVec() const {return plugins.getPluginsVec();}
                        std::map<std::string, std::map<std::string, std::vector<Plugin::PluginStruct>>> getPluginsMap() const {return plugins.getPluginsMap();}
                        
                        ~Gambit_Scanner();
                };             

        }
}

#endif
