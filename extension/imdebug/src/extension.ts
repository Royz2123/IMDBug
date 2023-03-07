import * as vscode from 'vscode';
import { subscribeToDocumentChanges, refreshDocumentNow, refreshModelNow, getModels } from './diagnostics';

export function activate(context: vscode.ExtensionContext) {
	const models = getModels()
	const diagnosticsCollection = vscode.languages.createDiagnosticCollection("imdbug");
	context.subscriptions.push(diagnosticsCollection);

	subscribeToDocumentChanges(context, diagnosticsCollection);

	context.subscriptions.push(
		vscode.commands.registerCommand('imdbug.activate', () => {
			vscode.window.showInformationMessage('IMDBug started working');
		})
	);

	context.subscriptions.push(
		vscode.commands.registerCommand('imdbug.refresh', () => {
			refreshDocumentNow(diagnosticsCollection);
		})
	);

	context.subscriptions.push(
		vscode.commands.registerCommand('imdbug.model', 
		async function () {
				const model = await vscode.window.showQuickPick(models, {
					matchOnDetail: true
				}).then(
					model => {
						if (!model) {
						  throw new Error('Error in extension trying to get model from user!');
						}
						const modelName = model.label;
						console.log("User selected: %s", modelName)
						refreshModelNow(diagnosticsCollection, modelName)
					  }
				)
			}
		
			
		)
	)
}

export function deactivate() {}
