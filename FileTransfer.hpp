/* ************************************************************************** */ // CAMBIOS
/*                                                                            */ // CAMBIOS
/*                                                        :::      ::::::::   */ // CAMBIOS
/*   FileTransfer.hpp                                   :+:      :+:    :+:   */ // CAMBIOS
/*                                                    +:+ +:+         +:+     */ // CAMBIOS
/*   By: Guille <Guille@student.42.fr>              +#+  +:+       +#+        */ // CAMBIOS
/*                                                +#+#+#+#+#+   +#+           */ // CAMBIOS
/*   Created: 2026/06/19 12:00:00 by Guille            #+#    #+#             */ // CAMBIOS
/*   Updated: 2026/06/19 12:00:00 by Guille           ###   ########.fr       */ // CAMBIOS
/*                                                                            */ // CAMBIOS
/* ************************************************************************** */ // CAMBIOS
// CAMBIOS
#ifndef FILETRANSFER_HPP // CAMBIOS
# define FILETRANSFER_HPP // CAMBIOS
// CAMBIOS
# include <string> // CAMBIOS
# include <fstream> // CAMBIOS
# include <ctime> // CAMBIOS
// CAMBIOS
class Client; // CAMBIOS
// CAMBIOS
enum TransferState // CAMBIOS
{ // CAMBIOS
	PENDING, // CAMBIOS
	TRANSFERRING, // CAMBIOS
	DONE, // CAMBIOS
	CANCELLED // CAMBIOS
}; // CAMBIOS
// CAMBIOS
class FileTransfer // CAMBIOS
{ // CAMBIOS
	public: // CAMBIOS
// CAMBIOS
		FileTransfer(int id, Client* sender, Client* receiver, // CAMBIOS
					const std::string& filename, const std::string& filepath); // CAMBIOS
		~FileTransfer(); // CAMBIOS
// CAMBIOS
		int         getId()       const; // CAMBIOS
		Client*     getSender()   const; // CAMBIOS
		Client*     getReceiver() const; // CAMBIOS
		std::string getFilename() const; // CAMBIOS
		std::string getFilepath() const; // CAMBIOS
		TransferState getState()  const; // CAMBIOS
		long        getFileSize() const; // CAMBIOS
		long        getBytesSent() const; // CAMBIOS
// CAMBIOS
		bool openFile(); // CAMBIOS
		void setState(TransferState state); // CAMBIOS
		int  sendChunk(int receiverFd); // CAMBIOS
		void closeFile(); // CAMBIOS
// CAMBIOS
	private: // CAMBIOS
// CAMBIOS
		FileTransfer(); // CAMBIOS
		FileTransfer(const FileTransfer&); // CAMBIOS
		FileTransfer& operator=(const FileTransfer&); // CAMBIOS
// CAMBIOS
		int           _id; // CAMBIOS
		Client*       _sender; // CAMBIOS
		Client*       _receiver; // CAMBIOS
		std::string   _filename; // CAMBIOS
		std::string   _filepath; // CAMBIOS
		TransferState _state; // CAMBIOS
		long          _fileSize; // CAMBIOS
		long          _bytesSent; // CAMBIOS
		std::ifstream _file; // CAMBIOS
}; // CAMBIOS
// CAMBIOS
#endif // CAMBIOS
