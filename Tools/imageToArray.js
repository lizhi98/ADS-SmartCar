import { Canvas, Image } from 'skia-canvas'
import fs from 'fs/promises'

const W = 188, H = 120
const canvas = new Canvas(W, H)
const ctx = canvas.getContext('2d')
const img = new Image()
const id = process.argv[2]
img.src = `./Test/Image/${id}.png`
await new Promise(res => img.onload = async () => {
	ctx.clearRect(0, 0, W, H)
	ctx.drawImage(img, 0, 0)

	const imageData = ctx.getImageData(0, 0, W, H).data
	const array = Array
		.from({ length: W * H })
		.map((_, i) => imageData[i * 4])
	await fs.writeFile(
		`./Test/Data/${id}.c`,
		`int image[${ H }][${ W }] = { ${ array.join(', ') } };`,
		'utf-8'
	)
	res()
})

