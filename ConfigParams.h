
struct ConfigurationAquarium {
    // Yeux
    Intervalle angleYeux = {30.0, 120.0};
    Intervalle distanceYeux = {50.0, 200.0};
    Intervalle gammaYeux = {0.5, 1.0};

    // Oreilles
    Intervalle distanceOreilles = {50.0, 250.0};
    Intervalle gammaOreilles = {0.5, 1.0};

    // Nageoires
    Intervalle nu = {1.0, 2.0};       // coeff vitesse
    //Carapace
    Intervalle coeff_mort = {0.1, 0.9} // coeff de reduction proba mort
    Intervalle eta = {0.1, 0.9};    // diminution vitesse
    //Camouflage
    Intervalle psi = {0.1, 0.9};  
};
