//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///  Master Likelihood container
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Christoph Weniger (c.weniger@uva.nl)
///  \date May 20 2013
///  \date June 03 2013
///
///
///  *********************************************

#ifndef __gambit_scan_hpp__
#define __gambit_scan_hpp__

#include <vector>
#include <unordered_map>
#include <string>
#include <functors.hpp>
#include <graphs.hpp>
#include <functors.hpp>

namespace GAMBIT
{
	namespace Scanner
	{
		using namespace GAMBIT;
		
		class Gambit_Scanner
		{
			
		protected:
			vector <double> upper_limits;
			vector <double> lower_limits;
			vector <std::string> keys;
			vector <std::string> functions;
			Graphs::DependencyResolver *dependencyResolver;
			std::unordered_map <std::string, std::pair<std::string, primary_model_functor *>> functors;
			std::string name;
			
		public:
			Gambit_Scanner (Graphs::DependencyResolver &a, std::map<std::string, primary_model_functor *> &activemodelFunctorMap, IniParser::IniFile &iniFile, std::string name) 
					: dependencyResolver(&a), name(name)
			{
				functions = iniFile.getValue<std::vector<std::string>>(name, "functions");
				
				for(std::map<std::string, primary_model_functor *>::iterator it = activemodelFunctorMap.begin(); it != activemodelFunctorMap.end(); it++) 
				{
					//it->first = model name, it->second = functor pointer
					std::vector <std::string> paramkeys = it->second->getcontentsPtr()->getKeys();
					for (std::vector<std::string>::iterator it2 = paramkeys.begin(); it2 != paramkeys.end(); ++it2)
					{
						string name = it->first + string("::") + *it2;
						functors[name].first = *it2;
						functors[name].second = it->second;
					}
				}
				
				keys = iniFile.getParameterList();
				lower_limits.resize(keys.size());
				upper_limits.resize(keys.size());
				std::vector<double>::iterator it_l = lower_limits.begin(), it_u = upper_limits.begin();
				for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it, ++it_l, ++it_u)
				{
					std::pair<double, double> range = iniFile.getParameterEntry< std::pair<double, double> >(*it, "range");
					std::string modelname = iniFile.getParameterEntry<std::string>(*it, "model");
					*it = modelname + string("::") + *it;
					if (range.first > range.second)
					{
						double temp = range.first;
						range.first = range.second;
						range.second = temp;
					}
					*it_l = range.first;
					*it_u = range.second;
				}
			}
			
			void InputParameters (std::vector<double> &vec) 
			{
				std::vector<double>::iterator it2 = vec.begin();
				for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it, ++it2)
					functors[*it].second->getcontentsPtr()->setValue(functors[*it].first, *it2);
			}
			
			void CalcPropose(Graphs::VertexID &it) {dependencyResolver->calcObsLike(it);}
			double GetPropose(Graphs::VertexID &it) {dependencyResolver->getObsLike(it);}
			
			const std::string Name() const {return name;}
			
			void Reset() {dependencyResolver->resetAll();}
			
			virtual int Run() = 0;
			
			friend class Scanner_Function_Base;
		};
		
		class Scanner_Function_Base
		{
		protected:
			std::vector<Graphs::VertexID> vertices;
			Gambit_Scanner *parent;
			
		public:
			Scanner_Function_Base(Gambit_Scanner *a, int funcNum) : parent(a)
			{
				vertices = parent->dependencyResolver->getObsLikeOrder();
				int size = 0;
				for (std::vector<Graphs::VertexID>::iterator it = vertices.begin(), it2 = vertices.begin(); it != vertices.end(); ++it)
				{
					if (parent->dependencyResolver->getIniEntry(*it)->purpose == parent->functions[funcNum])
					{
						*it2 = *it;
						it2++;
						size++;
					}
				}
				vertices.resize(size);
			}
		};
		
		template <class output, class input>
		class Scanner_Function : public Scanner_Function_Base
		{
		public:
			Scanner_Function (Gambit_Scanner *a, int funcNum) : Scanner_Function_Base (a, funcNum) {}
			
			virtual output & operator () (input in)
			{
				//Ben stuff
				//std::vector<Graphs::VertexID> OL = dependencyResolver.getObsLikeOrder();
			}
		};
		
		template <>
		class Scanner_Function <double, std::vector<double>> : public Scanner_Function_Base
		{
		public:
			Scanner_Function (Gambit_Scanner *a, int funcNum) : Scanner_Function_Base (a, funcNum) {}
			
			virtual double operator () (std::vector<double> &in)
			{
        cout << "1" << endl;
				parent->InputParameters(in);
        cout << "2" << endl;
				//std::vector<Graphs::VertexID> OL = dependencyResolver.getObsLikeOrder();
				double ret = 0;
        cout << "3" << endl;
				for (std::vector<Graphs::VertexID>::iterator it = vertices.begin(); it != vertices.end(); ++it)
				{
          cout << "4" << endl;
					parent->CalcPropose(*it);
					//dependencyResolver.notifyOfInvalidation(*it);
          cout << "5" << endl;
					ret += parent->GetPropose(*it);
				}
				
        cout << "6" << endl;
				parent->Reset();
				
        cout << "7" << endl;
				return ret;
			}
		};
		

	};
};

#endif
