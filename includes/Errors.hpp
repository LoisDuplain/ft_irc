#include <iostream>

#define BAD_CARACTERS "{}|[]\\"

#define ERR_NOSUCHNICK "<pseudo> :No such nick/channel"
//Utilisé pour indiquer que le pseudonyme passé en paramètre à la commande n'est pas actuellement utilisé.

#define ERR_NOSUCHSERVER "<nom de serveur> :No such server"
//Utilisé pour indiquer que le nom du serveur donné n'existe pas actuellement.

#define ERR_NOSUCHCHANNEL "<canal> :No such channel"
//Utilisé pour indiquer que le canal donné est invalide.

#define ERR_CANNOTSENDTOCHAN "<canal> :Cannot send to channel"
//Envoyé à un utilisateur qui (a) soit n'est pas dans un canal en mode +n ou (b) n'est pas opérateur (ou mode +v) sur un canal en mode +m ; et essaie d'envoyer un PRIVMSG à ce canal.

#define ERR_TOOMANYCHANNELS "<canal> :You have joined too many channels"
//Envoyé à un utilisateur quand il a atteint le nombre maximal de canaux qu'il est autorisé à accéder simultanément, s'il essaie d'en rejoindre un autre.

#define ERR_WASNOSUCHNICK "<canal> :There was no such nickname"
//Renvoyé par WHOWAS pour indiquer qu'il n'y a pas d'information dans l'historique concernant ce pseudonyme.

#define ERR_TOOMANYTARGETS "<destination> :Duplicate recipients. No message delivered"
//Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE utilisant le format de destination utilisateur@hôte pour lequel utilisateur@hôte a plusieurs occurrences.

#define ERR_NOORIGIN ":No origin specified"
//Message PING ou PONG sans le paramètre origine qui est obligatoire puisque ces commandes doivent marcher sans préfixe.

#define ERR_NORECIPIENT ":No recipient given (<commande>)"
//Pas de destinataire.

#define ERR_NOTEXTTOSEND ":No text to send"
//Pas de texte à envoyer.

#define ERR_NOTOPLEVEL "<masque> :No toplevel domain specified"
//Domaine principal non spécifié.

#define ERR_WILDTOPLEVEL "<masque> :Wildcard in toplevel domain"
//Joker dans le domaine principal

//Les erreurs 412-414 sont renvoyées par PRIVMSG pour indiquer que le message n'a pas été délivré. ERR_NOTOPLEVEL et ERR_WILDTOPLEVEL sont les erreurs renvoyées lors d'une utilisation invalide de "PRIVMSG $<serveur>" ou de "PRIVMSG #<hôte>".

#define ERR_UNKNOWNCOMMAND "<commande> :Unknown command"
//Renvoyé à un client enregistré pour indiquer que la commande envoyée est inconnue du serveur.

#define ERR_NOMOTD ":MOTD File is missing"
//Le fichier MOTD du serveur n'a pas pu être ouvert.

#define ERR_NOADMININFO "<serveur> :No administrative info available"
//Renvoyé par un serveur en réponse à un message ADMIN quand il y a une erreur lors de la recherche des informations appropriées.

#define ERR_FILEERROR ":File error doing <opération> on <fichier>"
//Message d'erreur générique utilisé pour rapporter un échec d'opération de fichier durant le traitement d'un message.

#define ERR_NONICKNAMEGIVEN ":No nickname given"
//Renvoyé quand un paramètre pseudonyme attendu pour une commande n'est pas fourni.

#define ERR_ERRONEUSNICKNAME "<pseudo> :Erroneus nickname"
//Renvoyé après la réception d'un message NICK qui contient des caractères qui ne font pas partie du jeu autorisé. Voir les sections 1 et 2.2 pour les détails des pseudonymes valides.

#define ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"
//Renvoyé quand le traitement d'un message NICK résulte en une tentative de changer de pseudonyme en un déjà existant.

#define ERR_NICKCOLLISION "<nick> :Nickname collision KILL"
//Renvoyé par un serveur à un client lorsqu'il détecte une collision de pseudonymes (enregistrement d'un pseudonyme qui existe déjà sur un autre serveur).

#define ERR_USERNOTINCHANNEL "<pseudo> <canal> :They aren't on that channel"
//Renvoyé par un serveur pour indiquer que l'utilisateur donné n'est pas dans le canal spécifié.

#define ERR_NOTONCHANNEL "<canal> :You're not on that channel"
//Renvoyé par le serveur quand un client essaie une commande affectant un canal dont il ne fait pas partie.

#define ERR_USERONCHANNEL "<utilisateur> <channel> :is already on channel"
//Renvoyé quand un client essaie d'inviter un utilisateur sur un canal où il est déjà.

#define ERR_NOLOGIN "<utilisateur> :User not logged in"
//Renvoyé par un SUMMON si la commande n'a pas pu être accomplie, car l'utilisateur n'est pas connecté.

#define ERR_SUMMONDISABLED ":SUMMON has been disabled"
//Renvoyé en réponse à une commande SUMMON si le SUMMON est désactivé. Tout serveur qui ne gère pas les SUMMON doit retourner cette valeur.

#define ERR_USERSDISABLED ":USERS has been disabled"
//Retourné en réponse à une commande USERS si la commande est désactivée. Tout serveur qui ne gère pas les USERS doit retourner cette valeur.

#define ERR_NOTREGISTERED ":You have not registered"
//Retourné par le serveur pour indiquer à un client qu'il doit être enregistré avant que ses commandes soient traitées.

#define ERR_NEEDMOREPARAMS "<commande> :Not enough parameters"
//Renvoyé par un serveur par de nombreuses commandes, afin d'indiquer que le client n'a pas fourni assez de paramètres.

#define ERR_ALREADYREGISTRED ":You may not reregister"
//Retourné par le serveur à tout lien qui tente de changer les détails enregistrés (tels que mot de passe et détails utilisateur du second message USER)

#define ERR_NOPERMFORHOST ":Your host isn't among the privileged"
//Renvoyé à un client qui essaie de s'enregistrer sur un serveur qui n'accepte pas les connexions depuis cet hôte.

#define ERR_PASSWDMISMATCH ":Password incorrect"
////Retourné pour indiquer l'échec d'une tentative d'enregistrement d'une connexion dû à un mot de passe incorrect ou manquant.

#define ERR_YOUREBANNEDCREEP ":You are banned from this server"
//Retourné après une tentative de connexion et d'enregistrement sur un serveur configuré explicitement pour vous refuser les connexions.

#define ERR_KEYSET "<canal> :Channel key already set"
//Clé de canal déjà définie.

#define ERR_CHANNELISFULL "<canal> :Cannot join channel (+l)"
//Impossible de joindre le canal (+l)

#define ERR_UNKNOWNMODE "<caractère> :is unknown mode char to me"
//Mode inconnu.

#define ERR_INVITEONLYCHAN "<canal> :Cannot join channel (+i)"
//Impossible de joindre le canal (+i).

#define ERR_BANNEDFROMCHAN "<canal> :Cannot join channel (+b)"
//Impossible de joindre le canal (+b).

#define ERR_BADCHANNELKEY "<canal> :Cannot join channel (+k)"
//Impossible de joindre le canal (+k).

#define ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
//Toute commande qui requiert le privilège d'opérateur pour opérer doit retourner cette erreur pour indiquer son échec.

#define ERR_CHANOPRIVSNEEDED "<canal> :You're not channel operator"
//Toute commande qui requiert les privilèges 'chanop' (tels les messages MODE) doit retourner ce message à un client qui l'utilise sans être chanop sur le canal spécifié.

#define ERR_CANTKILLSERVER ":You cant kill a server!"
//Toute tentative d'utiliser la commande KILL sur un serveur doit être refusée et cette erreur renvoyée directement au client.

#define ERR_NOOPERHOST ":No O-lines for your host"
//Si un client envoie un message OPER et que le serveur n'a pas été configuré pour autoriser les connexions d'opérateurs de cet hôte, cette erreur doit être retournée.

#define ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"
//Renvoyé par un serveur pour indiquer que le message MODE a été envoyé avec un pseudonyme et que le mode spécifié n'a pas été identifié.

#define ERR_USERSDONTMATCH ":Cant change mode for other users"
//Erreur envoyée à tout utilisateur qui essaie de voir ou de modifier le mode utilisateur d'un autre client.

std::string replaceErrorArgs(std::string err, std::string arg1, std::string arg2);