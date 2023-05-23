/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:17:07 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/23 17:17:15 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

# define BASH_DEFAULT "\033[0m" // Réinitialisation des paramètres par défaut

// Texte
# define BASH_BOLD "\033[1m"      // Texte en gras
# define BASH_UNDERLINE "\033[4m" // Texte souligné

// Couleurs du texte
# define BASH_BLACK "\033[30m"   // Texte en noir
# define BASH_RED "\033[31m"     // Texte en rouge
# define BASH_GREEN "\033[32m"   // Texte en vert
# define BASH_YELLOW "\033[33m"  // Texte en jaune
# define BASH_BLUE "\033[34m"    // Texte en bleu
# define BASH_MAGENTA "\033[35m" // Texte en magenta
# define BASH_CYAN "\033[36m"    // Texte en cyan
# define BASH_WHITE "\033[37m"   // Texte en blanc

// Couleurs de fond du texte
# define BASH_BG_BLACK "\033[40m"   // Fond du texte en noir
# define BASH_BG_RED "\033[41m"     // Fond du texte en rouge
# define BASH_BG_GREEN "\033[42m"   // Fond du texte en vert
# define BASH_BG_YELLOW "\033[43m"  // Fond du texte en jaune
# define BASH_BG_BLUE "\033[44m"    // Fond du texte en bleu
# define BASH_BG_MAGENTA "\033[45m" // Fond du texte en magenta
# define BASH_BG_CYAN "\033[46m"    // Fond du texte en cyan
# define BASH_BG_WHITE "\033[47m"   // Fond du texte en blanc

#endif