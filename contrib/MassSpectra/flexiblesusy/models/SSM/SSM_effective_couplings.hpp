// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Thu 10 May 2018 14:43:28

#ifndef SSM_EFFECTIVE_COUPLINGS_H
#define SSM_EFFECTIVE_COUPLINGS_H

#include "SSM_mass_eigenstates.hpp"
#include "lowe.h"
#include "physical_input.hpp"
#include "standard_model.hpp"

#include <complex>
#include <Eigen/Core>

namespace flexiblesusy {

namespace standard_model {
class Standard_model;
}

class SSM_effective_couplings {
public:
   SSM_effective_couplings(const SSM_mass_eigenstates&,
                                   const softsusy::QedQcd&,
                                   const Physical_input&);

   void do_run_couplings(bool flag) { rg_improve = flag; }
   bool do_run_couplings() const { return rg_improve; }
   void do_include_qcd_corrections(bool flag) { include_qcd_corrections = flag; }
   bool do_include_qcd_corrections() const { return include_qcd_corrections; }
   void set_physical_inputs(const Physical_input& inputs_) { physical_input = inputs_; }
   void set_low_energy_data(const softsusy::QedQcd& qedqcd_) { qedqcd = qedqcd_; }
   void set_model(const SSM_mass_eigenstates& model_);

   double get_hhVPVP_partial_width(int gO1) const;
   double get_hhVGVG_partial_width(int gO1) const;
   double get_AhVPVP_partial_width() const;
   double get_AhVGVG_partial_width() const;
   std::complex<double> get_eff_CphhVPVP(int gO1) const { return eff_CphhVPVP(gO1); }
   std::complex<double> get_eff_CphhVGVG(int gO1) const { return eff_CphhVGVG(gO1); }
   std::complex<double> get_eff_CpAhVPVP() const { return eff_CpAhVPVP; }
   std::complex<double> get_eff_CpAhVGVG() const { return eff_CpAhVGVG; }

   void calculate_effective_couplings();

   std::complex<double> CpbarFdFdAhPL(int gI1, int gI2) const;
   std::complex<double> CpbarFeFeAhPL(int gI1, int gI2) const;
   std::complex<double> CpbarFuFuAhPL(int gI1, int gI2) const;
   std::complex<double> CphhconjVWpVWp(int gI2) const;
   std::complex<double> CpbarFdFdhhPL(int gO2, int gI2, int gI1) const;
   std::complex<double> CpbarFeFehhPL(int gO2, int gI2, int gI1) const;
   std::complex<double> CpbarFuFuhhPL(int gO2, int gI2, int gI1) const;
   void calculate_eff_CphhVPVP(int gO1);
   void calculate_eff_CphhVGVG(int gO1);
   void calculate_eff_CpAhVPVP();
   void calculate_eff_CpAhVGVG();

private:
   SSM_mass_eigenstates model;
   softsusy::QedQcd qedqcd;
   Physical_input physical_input;
   bool rg_improve;
   bool include_qcd_corrections;

   void copy_mixing_matrices_from_model();

   standard_model::Standard_model initialise_SM() const;
   void run_SM_strong_coupling_to(standard_model::Standard_model, double m);

   // higher order corrections to the amplitudes for
   // effective coupling to photons
   std::complex<double> scalar_scalar_qcd_factor(double, double) const;
   std::complex<double> scalar_fermion_qcd_factor(double, double) const;
   std::complex<double> pseudoscalar_fermion_qcd_factor(double, double) const;

   // higher order corrections to the leading order
   // effective couplings to gluons
   double number_of_active_flavours(double) const;
   double scalar_scaling_factor(double) const;
   double pseudoscalar_scaling_factor(double) const;

   Eigen::Matrix<double,2,2> ZH{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<std::complex<double>,3,3> Vd{Eigen::Matrix<std::complex<double>,3,3>::Zero()};
   Eigen::Matrix<std::complex<double>,3,3> Ud{Eigen::Matrix<std::complex<double>,3,3>::Zero()};
   Eigen::Matrix<std::complex<double>,3,3> Vu{Eigen::Matrix<std::complex<double>,3,3>::Zero()};
   Eigen::Matrix<std::complex<double>,3,3> Uu{Eigen::Matrix<std::complex<double>,3,3>::Zero()};
   Eigen::Matrix<std::complex<double>,3,3> Ve{Eigen::Matrix<std::complex<double>,3,3>::Zero()};
   Eigen::Matrix<std::complex<double>,3,3> Ue{Eigen::Matrix<std::complex<double>,3,3>::Zero()};
   Eigen::Matrix<double,2,2> ZZ{Eigen::Matrix<double,2,2>::Zero()};

   Eigen::Array<std::complex<double>,2,1> eff_CphhVPVP;
   Eigen::Array<std::complex<double>,2,1> eff_CphhVGVG;
   std::complex<double> eff_CpAhVPVP;
   std::complex<double> eff_CpAhVGVG;

};

} // namespace flexiblesusy

#endif
