//============================================================================
//                                  I B E X
// File        : ibex_DefaultOptimizerConfig.h
// Author      : Gilles Chabert
// Copyright   : IMT Atlantique (France)
// License     : See the LICENSE file
// Created     : Dec 11, 2014
// Last Update : Oct 13, 2019
//============================================================================

#ifndef __IBEX_DEFAULT_OPTIMIZER_CONFIG_H__
#define __IBEX_DEFAULT_OPTIMIZER_CONFIG_H__

#include "ibex_OptimizerConfig.h"
#include "ibex_Memory.h"
#include "ibex_ExtendedSystem.h"

namespace ibex {

/**
 * \ingroup optim
 *
 * \brief Default optimizer configuration.
 *
 * The contractor is HC4 + acid(HC4) + X-Newton and the bisector is LSmear.
 *
 */
class DefaultOptimizerConfig : public OptimizerConfig, public Memory {
public:

	/**
	 * \brief Create default configuration
	 *
	 * \param sys         - The system to optimize.
	 */
	DefaultOptimizerConfig(const System& sys);

	/**
	 * \brief Delete this.
	 */
	virtual ~DefaultOptimizerConfig();

	/**
	 * \brief Set equality thickness.
	 *
	 * By default: #ExtendedSystem::default_eps_h.
	 *
	 */
	void set_eps_h(double eps_h);

	/**
	 * \brief Activate/deactivate rigor mode.
	 *
	 * If true, feasibility of equalities is certified.
	 * By default: true for unconstrained problems only.
	 */
	void set_rigor(bool rigor);

	/**
	 * \brief Activate/deactivate inHC4.
	 *
	 * If true, feasibility is also tried with LoupFinderInHC4.
	 * By default: #default_inHC4.
	 */
	void set_inHC4(bool inHC4);

	/**
	 * \brief Activate/deactivate KKT contractor.
	 *
	 * By default, we apply KKT and rigor mode only for unconstrained problems.
	 */
	void set_kkt(bool kkt);

	/**
	 * \brief Set random seed
	 *
	 * The sequence of random numbers is reinitialized with
	 * this seed before calling optimize(..) (useful for
	 * reproducibility).
	 *
	 * Set by default to #default_random_seed.
	 */
	void set_random_seed(double random_seed);

	/** \see #set_eps_h(). */
	double get_eps_h();

	/** \see #set_rigor(). */
	bool with_rigor();

	/** \see #set_inHC4(). */
	bool with_inHC4();

	/** \see #set_kkt(). */
	bool with_kkt();

	/** \see #set_random_seed(). */
	double get_random_seed();

	/** Default random seed: 1.0. */
	static constexpr double default_random_seed = 1.0;

	/** Default inHC4 mode: true (enabled). */
	static constexpr bool default_inHC4 = true;

	/** Default fix-point ratio for contraction based on linear relaxation. */
	static constexpr double default_relax_ratio = 0.2;

	/** Default ratio for choosing bisection point. */
	static constexpr double default_bisect_ratio = 0.5;

protected:

	// the following getters must be called only once the configuration
	// is over (all basic CONFIGeters are set) => reserved for Optimizer.
	virtual unsigned int nb_var();

	virtual Ctc& get_ctc();

	virtual Bsc& get_bsc();

	virtual LoupFinder& get_loup_finder();

	virtual CellBufferOptim& get_cell_buffer();

	virtual int goal_var();

	NormalizedSystem& get_norm_sys();

	ExtendedSystem& get_ext_sys();

	const System& sys;

	double eps_h;
	bool rigor;
	bool inHC4;
	bool kkt;
	double random_seed;
};


inline double DefaultOptimizerConfig::get_eps_h() { return eps_h; }

inline bool DefaultOptimizerConfig::with_rigor() { return rigor; }

inline bool DefaultOptimizerConfig::with_inHC4() { return inHC4; }

inline bool DefaultOptimizerConfig::with_kkt() { return kkt; }

inline double DefaultOptimizerConfig::get_random_seed() { return random_seed; }

} /* namespace ibex */

#endif /* __IBEX_DEFAULT_OPTIMIZER_CONFIG_H__ */
